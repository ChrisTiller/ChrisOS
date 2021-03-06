#include "../include/system.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <cstdlib>

using std::stringstream;
using std::ifstream;
using std::ofstream;

System* System::mInstance = NULL;

System* System::getInstance() {

    if (!mInstance) {
        mInstance = new System;
    }
    return mInstance;
};

void System::init() {

    IO::println("Welcome to ChrisOS!");
    IO::println("For a list of available commands, type help.");
}

void System::close() {

    exit(0);
}

void System::systemLoop() {

    Command userCommand;
    string mainCommand;
    bool finished = false;

    while (!finished) {

        userCommand.parseCommand(IO::getString(">"));

        mainCommand = userCommand.getMainCommand();

        if (mainCommand == "exit") {
            string ok = IO::getString("Are you sure? Y or N: ");
            if (ok == "Y" || ok == "y") {
                finished = true;
            }
        } else {

            if (!findCommand(userCommand)) {
                IO::println("Unrecognized command '" + mainCommand + "'. Type help for a list of available commands.");
            }
        }
    }
}

void System::loadSystemFunctions() {

    // "connecting" system functions with their command name
    systemFunctions.insert(std::make_pair("date", &System::getDate));
    systemFunctions.insert(std::make_pair("time", &System::getTime));
    systemFunctions.insert(std::make_pair("datetime", &System::getDateTime));
    systemFunctions.insert(std::make_pair("help", &System::help));
    systemFunctions.insert(std::make_pair("alias", &System::alias));
    systemFunctions.insert(std::make_pair("version", &System::getVersion));
    systemFunctions.insert(std::make_pair("suspend", &System::suspend));
    systemFunctions.insert(std::make_pair("resume", &System::resume));
    systemFunctions.insert(std::make_pair("setPriority", &System::setPriority));
    systemFunctions.insert(std::make_pair("showPCB", &System::showPCB));
    systemFunctions.insert(std::make_pair("showAll", &System::showAll));
    systemFunctions.insert(std::make_pair("showReady", &System::showReady));
    systemFunctions.insert(std::make_pair("showBlocked", &System::showBlocked));
    systemFunctions.insert(std::make_pair("SJF", &System::SJF));
    systemFunctions.insert(std::make_pair("FIFO", &System::FIFO));
    systemFunctions.insert(std::make_pair("STCF", &System::STCF));
    systemFunctions.insert(std::make_pair("FPPS", &System::FPPS));
    systemFunctions.insert(std::make_pair("RR", &System::RR));
    systemFunctions.insert(std::make_pair("MLFQ", &System::MLFQ));
}

bool System::findCommand(Command& command) {

    // tries to find the user specified command within the system function map
    // returns true if we found the command, false if we didn't

    string mainCommand;

    mainCommand = command.getMainCommand();

    // we need to check through our aliases just in case the user types in an aliased command
    map<string, string>::const_iterator aliasIt = aliasCommands.find(mainCommand);
    if (aliasIt != aliasCommands.end()) {
        // if we found that command, replace the mainCommand variable to that command
        mainCommand = aliasIt->second;
    }

    map<string, systemFunction>::const_iterator it = systemFunctions.find(mainCommand);
    if (it != systemFunctions.end()) {
        // look throught the system function map and see if the user specified command exists.
        // if so, execute it and return true
        // if not, continue and return false
        (this->*it->second)(command.getCommandParams());
        return true;
    }
    return false;
}

void System::alias(const vector<string>& params) {

    if (params.size() == 0) {
        IO::println("alias command takes 2 parameter");
        return;
    }

    if (params.at(0) == "help") {
        IO::println("\tCommand: alias <command name> <alias name>");
        IO::println("\tParameters:");
        IO::println("\t\t<command name> the name of the command you wish to alias.");
        IO::println("\t\t<alias name> the alias you wish to give to the command.");
        return;
    }

    if (params.size() != 2) {
        IO::println("alias command takes 2 parameter");
        return;
    }

    // does an entry in the map already contain the alias?
    map<string, string>::const_iterator it = aliasCommands.find(params.at(1));
    if (it == aliasCommands.end()) {

        // if not, does the command the user want to alias exist?
        map<string, systemFunction>::const_iterator it = systemFunctions.find(params.at(0));
        if (it != systemFunctions.end()) {

            // if so, add the entry to the map
            // if not, let the user know where they messed up and return
            aliasCommands.insert(std::make_pair(params.at(1), params.at(0)));
            IO::println("Command aliased successfully");
            return;
        } else {
            IO::println("The command '" + params.at(0) + "' does not exist.");
        }

    } else {
        IO::println("An alias with the name '" + params.at(1) + "' already exists");
    }
}

void System::getVersion(const vector<string>& params) {

    if (params.size() != 0) {
        IO::println("version does not take any parameters");
        return;
    }

    IO::println("ChrisOS - Version: 0.1.0");
}

void System::help(const vector<string>& params) {

    IO::println("Available Commands:");
    for (auto it = systemFunctions.begin(); it != systemFunctions.end(); it++) {
        IO::println("\t" + it->first);
    }
    IO::println("\texit");
    IO::println("For more information, enter the desired command followed by help");
}

void System::getDate(const vector<string>& params) {

    if (params.at(0) == "help") {
        IO::println("\tCommand: date <date format>");
        IO::println("\tParameters:");
        IO::println("\t\t<date format> - format for the date.");
        IO::println("\tReturn: returns the date with the specified format.");
        return;
        //return "date <date format> - returns current date with specified format";
    }

    if (params.size() != 1) {
        IO::println("date command takes 1 parameter");
        return;
    }

    struct tm *now;
	time_t tNow = time(0);
	now = localtime(&tNow);

    string stringDate = "";
    string dateFormat = params.at(0);

	if (dateFormat == "mm/dd/yy") {


        // if the month begins with 1-9, we need to add an extra 0 in the front to meet format requirements.
		if ((now->tm_mon + 1) < 10) {
			stringDate += "0";
		}

		stringDate += std::to_string(now->tm_mon + 1) +  "/";

        // if the day begins with 1-9, we need to add an extra 0 in the front to meet format requirements.
		if (now->tm_mday < 10) {
			stringDate += "0";
		}

		stringDate += std::to_string(now->tm_mday) + "/";

        // tm_year contains the number of years that have passed since 1900 so we need to add that in
		stringDate += std::to_string((now->tm_year + 1900) % 100);

	} else if (dateFormat == "dd/mm/yy") {

		if (now->tm_mday < 10) {
			stringDate += "0";
		}

		stringDate += std::to_string(now->tm_mday) + "/";

		if ((now->tm_mon + 1) < 10) {
			stringDate += "0";
		}

		stringDate += std::to_string(now->tm_mon + 1) +  "/";

		stringDate += std::to_string((now->tm_year + 1900) % 100);

	} else if (dateFormat == "mm/dd/yyyy") {

		if ((now->tm_mon + 1) < 10) {
			stringDate += "0";
		}

		stringDate += std::to_string(now->tm_mon + 1) + "/";

		if (now->tm_mday < 10) {
			stringDate += "0";
		}

		stringDate += std::to_string(now->tm_mday) + "/";

		stringDate += std::to_string(now->tm_year + 1900);

	} else if (dateFormat == "dd/mm/yyyy") {

		if (now->tm_mday < 10) {
			stringDate += "0";
		}

		stringDate += std::to_string(now->tm_mday) + "/";

		if ((now->tm_mon + 1) < 10) {
			stringDate += "0";
		}

		stringDate += std::to_string(now->tm_mon + 1) +  "/";

		stringDate += std::to_string(now->tm_year + 1900);

	} else if (dateFormat == "m/d/yyyy") {

		stringDate = (std::to_string(now->tm_mon + 1) + "/" + std::to_string(now->tm_mday) + "/" + std::to_string(now->tm_year + 1900));
	} else if (dateFormat == "m/d/yy") {

		stringDate = (std::to_string(now->tm_mon + 1) + "/" + std::to_string(now->tm_mday) + "/" + std::to_string((now->tm_year + 1900) % 100));
    } else if (dateFormat == "d/m/yyyy") {

		stringDate = (std::to_string(now->tm_mday) + "/" + std::to_string(now->tm_mon + 1) + "/" + std::to_string(now->tm_year + 1900));
	} else if (dateFormat == "d/m/yy") {

		stringDate = (std::to_string(now->tm_mday) + "/" + std::to_string(now->tm_mon + 1) + "/" + std::to_string((now->tm_year + 1900) % 100));
	} else {
        IO::println("unrecognized date format");
	}

	IO::println(stringDate);
}

void System::getTime(const vector<string>& params) {

    // returns the time with the specified format

    if (params.at(0) == "help") {
        IO::println("\tCommand: time <time format>");
        IO::println("\tParameters:");
        IO::println("\t\t<time format> - format for the time.");
        IO::println("\tReturn: returns the time with the specified format.");
        return;
        //return "date <date format> - returns current date with specified format";
    }

    if (params.size() != 1) {
        IO::println("date command takes 1 parameter");
        return;
    }

    struct tm *now;
	time_t tNow = time(0);
	now = localtime(&tNow);

	string stringTime = "";
	string timeFormat = params.at(0);
	bool isMorning = true;

    if (timeFormat == "hh:mm:ss") {

		if (now->tm_hour < 10) {
			stringTime += "0" + std::to_string(now->tm_hour);
		}
		else if (now->tm_hour > 12) {
            // we dont want military time so subtract 12 if the hour is over 12
			stringTime += "0" + std::to_string(now->tm_hour - 12);
			isMorning = false;
		} else {
			stringTime += std::to_string(now->tm_hour);
		}

		if (now->tm_hour == 0) {
            stringTime = "12";
		}

		stringTime += ":";

		if (now->tm_min < 10) {
			stringTime += "0";
		}

		stringTime += std::to_string(now->tm_min) + ":";

		if (now->tm_sec < 10) {
			stringTime += "0";
		}

		stringTime += std::to_string(now->tm_sec);
	}
	else if (timeFormat == "h:m:s") {

		if (now->tm_hour > 12) {

			stringTime += std::to_string(now->tm_hour - 12);
			isMorning = false;
		}
		else {

			stringTime += std::to_string(now->tm_hour);
		}

		if (now->tm_hour == 0) {
            stringTime = "12";
		}

		stringTime += ":";

		stringTime += std::to_string(now->tm_min);

		stringTime += ":";

		stringTime += std::to_string(now->tm_sec);
	}
	else if (timeFormat == "h:m") {

		if (now->tm_hour > 12) {

			stringTime += std::to_string(now->tm_hour - 12);
			isMorning = false;
		} else {

			stringTime += std::to_string(now->tm_hour);
		}

		if (now->tm_hour == 0) {
            stringTime = "12";
		}

		stringTime += ":";

		stringTime += std::to_string(now->tm_min);
	}
	else if (timeFormat == "hh:mm") {

		if (now->tm_hour < 10) {
			stringTime += "0" + std::to_string(now->tm_hour);
		} else if (now->tm_hour > 12) {
			stringTime += "0" + std::to_string(now->tm_hour - 12);
			isMorning = false;
		} else {
			stringTime += std::to_string(now->tm_hour);
		}

		if (now->tm_hour == 0) {
            stringTime = "12";
		}

		stringTime += ":";

		if (now->tm_min < 10) {
			stringTime += "0";
		}

		stringTime += std::to_string(now->tm_min);
	} else {
        IO::println("unrecognized time format");
        return;
	}

	if (isMorning) {
		IO::println(stringTime + " AM");
	} else {
		IO::println(stringTime + " PM");
	}
}

void System::getDateTime(const vector<string> &params) {

    // returns the date and the time

    if (params.at(0) == "help") {
        IO::println("\tCommand: datetime <date format> <time format>");
        IO::println("\tParameters:");
        IO::println("\t\t<date format> - format for the date.");
        IO::println("\t\t<time format> - format for the time.");
        IO::println("\tReturn: returns both the date and the time with the specified format.");
        return;
        //return "datetime <date format> < time format> - returns both the date and the time with the specified format.";
    }

    if (params.size() != 2) {
        IO::println("datetime takes 2 parameters.");
        return;
    }

    getDate(vector<string>(params.begin(), params.begin() + 1));
    getTime(vector<string>(params.begin() + 1, params.begin() + 2));
}

PCB* System::allocatePCB() {

    return new PCB();
}

void System::freePCB(PCB* pcb) {

    assert(pcb != NULL);

    delete pcb;
}

PCB* System::setupPCB(string name, int priority, PROCESS_CLASS processClass) {

    if (findPCB(name) == NULL) {

        PCB* newPCB = allocatePCB();

        if ((priority < -127) || (priority > 128)) {
            IO::println("Invalid priority value");
            return NULL;
        }

        newPCB->setName(name);
        newPCB->setPrioirty(priority);
        newPCB->setProcessClass(processClass);
        newPCB->setState(READY);
        newPCB->setSuspend(false);

        return newPCB;

    }
    return NULL;
}

PCB* System::findPCB(string name) {

    PCB* pcb = mReadyQueue.contains(name);

    if (pcb != NULL) {
        return pcb;
    }

    pcb = mBlockedQueue.contains(name);

    if (pcb != NULL) {
        return pcb;
    }
    return NULL;
}

void System::insertPCB(PCB* pcb) {

    assert(pcb != NULL);

    if (pcb->getState() == READY) {

        mReadyQueue.push_back(pcb);

    } else {

        mBlockedQueue.push_back(pcb);

    }
}

bool System::removePCB(PCB* pcb) {

    assert(pcb != NULL);

    PCB* toRemove = findPCB(pcb->getName());

    if (toRemove != NULL) {

        if (toRemove->getState() == READY) {

            if (mReadyQueue.remove(pcb)) {
                return true;
            }

        } else {

            if (mBlockedQueue.remove(pcb)) {
                return true;
            }
        }
    }
    return false;
}

void System::suspend(const vector<string>& params) {

     if (params.size() == 0) {
        IO::println("suspend takes 1 parameter");
        return;
    }

    if (params.at(0) == "help") {
        IO::println("\tCommand: suspend <process name>");
        IO::println("\tParameters:");
        IO::println("\t\t<process name> - the name of the process");
        //IO::println("\tReturn: returns both the date and the time with the specified format.");
        return;
    }

    if (params.size() != 1) {
        IO::println("suspend takes 1 parameter1");
        return;
    }

    PCB* pcb = findPCB(params.at(0));

    if (pcb == NULL) {
        IO::println("A process with the given name does not exist");
        return;
    }

    pcb->setSuspend(true);

    IO::println("Process sucesfully suspended");
}

void System::resume(const vector<string>& params) {

     if (params.size() == 0) {
        IO::println("resume takes 1 parameter");
        return;
    }

    if (params.at(0) == "help") {
        IO::println("\tCommand: resume <process name>");
        IO::println("\tParameters:");
        IO::println("\t\t<process name> - the name of the process");
        //IO::println("\tReturn: returns both the date and the time with the specified format.");
        return;
    }

    if (params.size() != 1) {
        IO::println("resume takes 1 parameter1");
        return;
    }

    PCB* pcb = findPCB(params.at(0));

    if (pcb == NULL) {
        IO::println("A process with the given name does not exist");
        return;
    }

    pcb->setSuspend(false);

    IO::println("Process sucesfully resumed");
}

void System::setPriority(const vector<string>& params) {

     if (params.size() == 0) {
        IO::println("setPriority takes 2 parameter");
        return;
    }

    if (params.at(0) == "help") {
        IO::println("\tCommand: setPriority <process name> <priority value>");
        IO::println("\tParameters:");
        IO::println("\t\t<process name> - the name of the process");
        IO::println("\t\t<priority value> - the priority value for the process");
        //IO::println("\tReturn: returns both the date and the time with the specified format.");
        return;
    }

    if (params.size() != 2) {
        IO::println("setPriority takes 2 parameter1");
        return;
    }

    PCB* pcb = findPCB(params.at(0));

    if (pcb == NULL) {
        IO::println("A process with the given name does not exist");
        return;
    }

    int newVal = atoi(params.at(1).c_str());

    if ((newVal < -127) || (newVal > 128)) {
        IO::println("Invalud priority value " + params.at(1));
        return;
    }

    pcb->setPrioirty(newVal);

    IO::println("Priority sucesfully changed");
}

void System::showPCB(const vector<string>& params) {

    if (params.size() == 0) {
        IO::println("showPCB takes 1 parameter");
        return;
    }

    if (params.at(0) == "help") {
        IO::println("\tCommand: showPCB <process name>");
        IO::println("\tParameters:");
        IO::println("\t\t<process name> - the name of the process");
        return;
    }

    if (params.size() != 1) {
        IO::println("showPCB takes 1 parameter");
        return;
    }

    PCB* pcb = findPCB(params.at(0));

    if (pcb == NULL) {
        IO::println("A process with the given name does not exist");
        return;
    }

    for (int i = 0; i < mWidth; i++) {
        IO::print("*");
    }

    IO::println("*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED |MEMEORY*");
    IO::println("*-------------------------|-----------|----------|---------|-----------|-------*");

    displayPCBInfo(pcb);

    for (int i = 0; i < mWidth; i++) {
        IO::print("*");
    }
}

void System::showAll(const vector<string>& params) {

    if (params.size() != 0) {
        IO::println("showAll takes 0 parameters");
        return;
    }

    if (mReadyQueue.numPCB() == 0 && mBlockedQueue.numPCB() == 0) {
        IO::println("No PCB's to show");
        return;
    }

    for (int i = 0; i < mWidth; i++) {
        IO::print("*");
    }

    IO::println("*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED |MEMEORY*");
    IO::println("*-------------------------|-----------|----------|---------|-----------|-------*");

    int currLineNo = 3;

    if (mReadyQueue.numPCB() > 0) {

        for (PCB* pcb = mReadyQueue.begin(); pcb != mReadyQueue.end(); pcb = pcb->getNext()) {
            displayPCBInfo(pcb);

            currLineNo++;

            if (currLineNo == mHeight - 1) {

                IO::getString("Press any key to continue..");

                IO::println("*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED |MEMEORY*");
                IO::println("*-------------------------|-----------|----------|---------|-----------|-------*");

                currLineNo = 3;

            }
        }
    }

    if (mBlockedQueue.numPCB() > 0) {

        for (PCB* pcb = mBlockedQueue.begin(); pcb != mBlockedQueue.end(); pcb = pcb->getNext()) {
            displayPCBInfo(pcb);

            currLineNo++;

            if (currLineNo == mHeight - 1) {

                IO::getString("Press any key to continue..");

                IO::println("*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED |MEMEORY*");
                IO::println("*-------------------------|-----------|----------|---------|-----------|-------*");

                currLineNo = 3;

            }
        }
    }

     for (int i = 0; i < mWidth; i++) {
        IO::print("*");
    }
}

void System::displayPCBInfo(PCB* pcb) {

    assert(pcb != NULL);

    if (pcb->getName().length() > 27) {
        IO::print("*" + pcb->getName().substr(0, 22) + "...|");
    } else {
        IO::print("*" + pcb->getName());

        for (int i = pcb->getName().length(); i < 25; i++) {
            IO::print(" ");
        }

        IO::print("|");
    }

    if (pcb->getProcessClass() == SYSTEM) {
        IO::print("SYSTEM     |");
    } else {
        IO::print("APPLICATION|");
    }

    IO::print(std::to_string(pcb->getPriority()));

    for (int i = std::to_string(pcb->getPriority()).length(); i < 10; i++) {
        IO::print(" ");
    }

    IO::print("|");

    if (pcb->getState() == READY) {
        IO::print("READY    |");
    } else {
        IO::print("BLOCKED  |");
    }

    if (pcb->getSuspend()) {
        IO::print("YES        |");
    } else {
        IO::print("NO         |");
    }

    IO::print(std::to_string(pcb->getMemory()));

    for (int i = std::to_string(pcb->getMemory()).length(); i < 7; i++) {
        IO::print(" ");
    }

    IO::print("*");
}

void System::showReady(const vector<string>& params) {

    if (params.size() != 0) {
        IO::println("showReady takes 0 parameters");
        return;
    }

    if (mReadyQueue.numPCB() == 0) {
        IO::println("No PCB's to show");
        return;
    }

    for (int i = 0; i < mWidth; i++) {
        IO::print("*");
    }

    IO::println("*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED |MEMEORY*");
    IO::println("*-------------------------|-----------|----------|---------|-----------|-------*");

    int currLineNo = 3;

    for (PCB* pcb = mReadyQueue.begin(); pcb != mReadyQueue.end(); pcb = pcb->getNext()) {
        displayPCBInfo(pcb);

        currLineNo++;

        if (currLineNo == mHeight - 1) {

            IO::getString("Press any key to continue..");

            IO::println("*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED |MEMEORY*");
            IO::println("*-------------------------|-----------|----------|---------|-----------|-------*");

            currLineNo = 3;

        }
    }

     for (int i = 0; i < mWidth; i++) {
        IO::print("*");
    }
}

void System::showBlocked(const vector<string>& params) {

    if (params.size() != 0) {
        IO::println("showBlocked takes 0 parameters");
        return;
    }

    if (mBlockedQueue.numPCB() == 0) {
        IO::println("No PCB's to show");
        return;
    }

    for (int i = 0; i < mWidth; i++) {
        IO::print("*");
    }

    IO::println("*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED |MEMEORY*");
    IO::println("*-------------------------|-----------|----------|---------|-----------|-------*");

    int currLineNo = 3;

    for (PCB* pcb = mBlockedQueue.begin(); pcb != mBlockedQueue.end(); pcb = pcb->getNext()) {
        displayPCBInfo(pcb);

        currLineNo++;

        if (currLineNo == mHeight - 1) {

            IO::getString("Press any key to continue..");

            IO::println("*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED |MEMEORY*");
            IO::println("*-------------------------|-----------|----------|---------|-----------|-------*");

            currLineNo = 3;

        }
    }

     for (int i = 0; i < mWidth; i++) {
        IO::print("*");
    }
}

void System::SJF(const vector<string>& params) {

    if (params.size() != 1) {
        IO::println("SJF takes only one parameter");
        return;
    }

    pcbQueue bufferQueue;

    vector<pcbTime> times;

    loadJobs(params, bufferQueue);

    PCB* lowestTimeRemaining;

    // we then look through our buffer queue to find the process with the lowest time remaining.
    // once we find it, remove it from the buffer queue and place into the ready queue
    // repeat until buffer queue is empty
    while (bufferQueue.numPCB() > 0) {

        lowestTimeRemaining = bufferQueue.cbegin();

        for (PCB* pcb2 = bufferQueue.cbegin(); pcb2 != bufferQueue.cend(); pcb2 = pcb2->getNext()) {
            if (((int)pcb2->getTimeRemaining()) < ((int)lowestTimeRemaining->getTimeRemaining())) {
                lowestTimeRemaining = pcb2;
            }
        }

        bufferQueue.remove(lowestTimeRemaining);
        mReadyQueue.push_back(lowestTimeRemaining);
    }

    showReady(vector<string>());

    pcbTime time;
    int completionTime = 0;

    while (mReadyQueue.numPCB() > 0) {
        PCB* frontPCB = mReadyQueue.pop_front();
        IO::println(frontPCB->getName());

        time.completionTime = completionTime + frontPCB->getTimeRemaining();
        completionTime = completionTime + frontPCB->getTimeRemaining();

        time.arrivalTime = 0;

        times.push_back(time);

        freePCB(frontPCB);
    }

    IO::println("Turnaround Time: " + std::to_string(computeTurnaround(times)) + " cycles");

}

void System::FIFO(const vector<string>& params) {

    if (params.size() != 1) {
        IO::println("FIFO takes only one parameter");
        return;
    }

    pcbQueue bufferQueue;
    vector<pcbTime> times;

    loadJobs(params, bufferQueue);

    int currentCycle = 0;

    while (!bufferQueue.isEmpty() || !mReadyQueue.isEmpty()) {

        if (!bufferQueue.isEmpty()) {
            while (bufferQueue.begin()->getArrivalTime() == currentCycle) {
                PCB* pcb = bufferQueue.pop_front();

                mReadyQueue.push_back(pcb);

                displayQueueInfo("FIFO.txt", "New Process added: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());
            }
        }

        currentCycle++;
        pcbTime time;

        if (!mReadyQueue.isEmpty()) {
            mReadyQueue.begin()->setTimeRemaining(mReadyQueue.begin()->getTimeRemaining() - 1);

            if (mReadyQueue.begin()->getTimeRemaining() == 0) {
                PCB* pcb = mReadyQueue.pop_front();

                IO::println(pcb->getName());

                time.arrivalTime = pcb->getArrivalTime();
                time.completionTime = currentCycle;

                times.push_back(time);

                displayQueueInfo("FIFO.txt", "Process finished: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                freePCB(pcb);
            }
        }
    }

    IO::println("Turnaround Time: " + std::to_string(computeTurnaround(times)) + " cycles");
}

void System::loadJobs(const vector<string>& params, pcbQueue& jobQueue) {

    ifstream file;

    if (!file.is_open()) {
        file.open(params.at(0), std::ios_base::in);
    }

    if (file.fail()) {
        IO::println("File failed to open");
        return;
    }

    vector<string> tokens;
    string line;


    // we first read in the contents of the file.
    // since this is a full knowledge scheduler, we read the entire file before insertions to the ready queue
    while (std::getline(file, line)) {

        // break each line into tokens
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' ')) {
            tokens.push_back(token);
        }

        PCB* pcb;

        // tokens.at(0) is the process name
        // tokens.at(1) is the process class
        // tokens.at(2) is the process priority
        // tokens.at(3) is the memory
        // tokens.at(4) is the time remaining
        // tokens.at(5) is the time of arrival
        // tokens.at(6) is the percent of CPU
        if (tokens.at(1) == "A") {
            pcb = setupPCB(tokens.at(0), atoi(tokens.at(2).c_str()), APPLICATION);
        } else {
            pcb = setupPCB(tokens.at(0), atoi(tokens.at(2).c_str()), SYSTEM);
        }

        pcb->setMemory(atoi(tokens.at(3).c_str()));
        pcb->setTimeRemaining(atoi(tokens.at(4).c_str()));
        pcb->setArrivalTime(atoi(tokens.at(5).c_str()));
        pcb->setPercentOfCPU(atoi(tokens.at(6).c_str()));

        jobQueue.push_back(pcb);

        tokens.clear();

    }

    file.close();

}

void System::STCF(const vector<string>& params) {

    if (params.size() != 1) {
        IO::println("STCF takes only one parameter");
        return;
    }

    pcbQueue bufferQueue;
    vector<pcbTime> times;

    loadJobs(params, bufferQueue);

    int currentCycle = 0;

    while (!bufferQueue.isEmpty() || !mReadyQueue.isEmpty()) {

        if (!bufferQueue.isEmpty()) {
            while (bufferQueue.begin()->getArrivalTime() == currentCycle) {
                PCB* pcb = bufferQueue.pop_front();

                mReadyQueue.push_back(pcb);

                displayQueueInfo("STCF.txt", "New Process added: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                PCB* temp;

                for (PCB* pcb2 = mReadyQueue.begin(); pcb2 != mReadyQueue.end(); pcb2 = pcb2->getNext()) {

                    if (pcb->getTimeRemaining() < pcb2->getTimeRemaining()) {
                        temp = pcb2->getPrev();
                        mReadyQueue.remove(pcb2);
                        mReadyQueue.push_back(pcb2);

                        displayQueueInfo("STCF.txt", "Process Kicked Out: " + pcb2->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                        pcb2 = temp;
                    }

                    if (pcb2 == pcb) {
                        pcb2 = mReadyQueue.end()->getPrev();
                    }
                }
            }
        }

        currentCycle++;

        pcbTime time;

        if (!mReadyQueue.isEmpty()) {

            mReadyQueue.begin()->setTimeRemaining(mReadyQueue.begin()->getTimeRemaining() - 1);

            if (mReadyQueue.begin()->getTimeRemaining() == 0) {
                PCB* pcb = mReadyQueue.pop_front();

                IO::println(pcb->getName());

                time.arrivalTime = pcb->getArrivalTime();
                time.completionTime = currentCycle;

                times.push_back(time);

                displayQueueInfo("STCF.txt", "Process Finished: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                freePCB(pcb);
            }
        }
    }

    IO::println("Turnaround Time: " + std::to_string(computeTurnaround(times)) + " cycles");

}

void System::FPPS(const vector<string>& params) {

    if (params.size() != 1) {
        IO::println("FFPS takes only one parameter");
        return;
    }

    pcbQueue bufferQueue;
    vector<pcbTime> times;

    loadJobs(params, bufferQueue);

    int currentCycle = 0;

    while (!bufferQueue.isEmpty() || !mReadyQueue.isEmpty()) {

        if (!bufferQueue.isEmpty()) {
            while (bufferQueue.begin()->getArrivalTime() == currentCycle) {
                PCB* pcb = bufferQueue.pop_front();

                mReadyQueue.push_back(pcb);

                displayQueueInfo("FPPS.txt", "New Process added: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                PCB* temp;

                for (PCB* pcb2 = mReadyQueue.begin(); pcb2 != mReadyQueue.end(); pcb2 = pcb2->getNext()) {

                    if (pcb->getPriority() > pcb2->getPriority()) {
                        temp = pcb2->getPrev();
                        mReadyQueue.remove(pcb2);
                        mReadyQueue.push_back(pcb2);

                        displayQueueInfo("FPPS.txt", "Process Kicked Out: " + pcb2->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                        pcb2 = temp;
                    }

                    if (pcb2 == pcb) {
                        pcb2 = mReadyQueue.end()->getPrev();
                    }
                }
            }
        }

        currentCycle++;
        pcbTime time;

        if (!mReadyQueue.isEmpty()) {

            mReadyQueue.begin()->setTimeRemaining(mReadyQueue.begin()->getTimeRemaining() - 1);

            if (mReadyQueue.begin()->getTimeRemaining() == 0) {
                PCB* pcb = mReadyQueue.pop_front();

                IO::println(pcb->getName());

                time.arrivalTime = pcb->getArrivalTime();
                time.completionTime = currentCycle;

                times.push_back(time);

                displayQueueInfo("FPPS.txt", "Process Finished: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                freePCB(pcb);
            }
        }
    }

    IO::println("Turnaround Time: " + std::to_string(computeTurnaround(times)) + " cycles");
}

void System::RR(const vector<string>& params) {

    if (params.size() != 2) {
        IO::println("RR takes two parameters");
        return;
    }

    pcbQueue bufferQueue;
    vector<pcbTime> times;

    loadJobs(params, bufferQueue);

    int currentCycle = 0;
    int quantum = atoi(params.at(1).c_str());
    int quantumCounter = 0;

    while (!bufferQueue.isEmpty() || !mReadyQueue.isEmpty()) {

        if (!bufferQueue.isEmpty()) {
            while (bufferQueue.begin()->getArrivalTime() == currentCycle) {
                PCB* pcb = bufferQueue.pop_front();

                mReadyQueue.push_back(pcb);

                displayQueueInfo("RR.txt", "Process Added: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

            }
        }

        currentCycle++;
        quantumCounter++;

        pcbTime time;

        if (!mReadyQueue.isEmpty()) {

            mReadyQueue.begin()->setTimeRemaining(mReadyQueue.begin()->getTimeRemaining() - 1);

            if (mReadyQueue.begin()->getTimeRemaining() == 0) {
                PCB* pcb = mReadyQueue.pop_front();

                IO::println(pcb->getName());

                time.arrivalTime = pcb->getArrivalTime();
                time.completionTime = currentCycle;

                times.push_back(time);

                displayQueueInfo("RR.txt", "Process Finished: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                freePCB(pcb);

                quantumCounter = 0;
            }

            if (quantumCounter == quantum) {

                PCB* pcb = mReadyQueue.pop_front();
                mReadyQueue.push_back(pcb);


                displayQueueInfo("RR.txt", "Process Pre-empted: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                quantumCounter = 0;
            }
        }
    }

    IO::println("Turnaround Time: " + std::to_string(computeTurnaround(times)) + " cycles");
}

void System::MLFQ(const vector<string>& params) {

    if (params.size() != 4) {
        IO::println("MLFQ takes four parameters");
        return;
    }

    pcbQueue bufferQueue;
    pcbQueue sortingQueue;
    vector<pcbTime> times;

    loadJobs(params, bufferQueue);

    int currentCycle = 0;
    int quantum = atoi(params.at(2).c_str());
    int quantumCounter = 0;

    int numQueues = atoi(params.at(1).c_str());
    int maxCycles = atoi(params.at(3).c_str());
    int cycleCounter = 0;

    int priorityToRun = numQueues - 1;

    while (!bufferQueue.isEmpty() || !mReadyQueue.isEmpty()) {

        if (!bufferQueue.isEmpty()) {

            while (bufferQueue.begin()->getArrivalTime() == currentCycle) {

                PCB* pcb = bufferQueue.pop_front();

                pcb->setPrioirty(numQueues - 1);

                mReadyQueue.push_back(pcb);

                while (!mReadyQueue.isEmpty()) {

                    sortingQueue.push_back(mReadyQueue.pop_front());

                }

                PCB* highestPriority;

                while (!sortingQueue.isEmpty()) {

                    highestPriority = sortingQueue.cbegin();

                    for (PCB* pcb2 = sortingQueue.cbegin(); pcb2 != sortingQueue.cend(); pcb2 = pcb2->getNext()) {
                        if ((pcb2->getPriority()) > (highestPriority->getPriority())) {
                            highestPriority = pcb2;
                        }
                    }

                    sortingQueue.remove(highestPriority);
                    mReadyQueue.push_back(highestPriority);

                }

                displayQueueInfo("MLFQ.txt", "Process Added: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

            }
        }

        currentCycle++;
        cycleCounter++;

        pcbTime time;

        if (!mReadyQueue.isEmpty()) {

            if (mReadyQueue.begin()->getPriority() == priorityToRun) {

                quantumCounter++;

                mReadyQueue.begin()->setTimeRemaining(mReadyQueue.begin()->getTimeRemaining() - 1);


                if (mReadyQueue.begin()->getTimeRemaining() == 0) {
                    PCB* pcb = mReadyQueue.pop_front();

                    IO::println(pcb->getName());

                    time.arrivalTime = pcb->getArrivalTime();
                    time.completionTime = currentCycle;

                    times.push_back(time);

                    displayQueueInfo("MLFQ.txt", "Process Finished: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                    freePCB(pcb);

                    quantumCounter = 0;
                }

                // if a process doesn't finish within its time slice, it gets pre-empted and reduced priority
                if (quantumCounter == quantum) {

                    PCB* pcb = mReadyQueue.pop_front();

                    if (pcb->getPriority() > 0) {
                        pcb->setPrioirty(pcb->getPriority() - 1);
                    }

                    mReadyQueue.push_back(pcb);

                    while (!mReadyQueue.isEmpty()) {
                        sortingQueue.push_back(mReadyQueue.pop_front());
                    }

                    PCB* highestPriority;

                    while (!sortingQueue.isEmpty()) {

                        highestPriority = sortingQueue.cbegin();

                        for (PCB* pcb2 = sortingQueue.cbegin(); pcb2 != sortingQueue.cend(); pcb2 = pcb2->getNext()) {
                            if ((pcb2->getPriority()) > (highestPriority->getPriority())) {
                                highestPriority = pcb2;
                            }
                        }

                        sortingQueue.remove(highestPriority);
                        mReadyQueue.push_back(highestPriority);
                    }

                    displayQueueInfo("MLFQ.txt", "Process Pre-empted: " + pcb->getName() + "\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                    quantumCounter = 0;
                }

                // if the cycleCounter reaches the maxCycles, all process in the queue goes back to the highes priority
                if (cycleCounter == maxCycles) {

                    for (PCB* pcb = mReadyQueue.begin(); pcb != mReadyQueue.end(); pcb = pcb->getNext()) {
                        pcb->setPrioirty(numQueues - 1);
                    }

                    displayQueueInfo("MLFQ.txt", "Process Priority Reset\nCurrent Cycle No.: " + std::to_string(currentCycle) + "\nRunning Process: " + mReadyQueue.begin()->getName());

                    cycleCounter = 0;

                }
            }
            priorityToRun = mReadyQueue.begin()->getPriority();
        }
    }

    IO::println("Turnaround Time: " + std::to_string(computeTurnaround(times)) + " cycles");
}

void System::displayQueueInfo(string fileName, string message) {

    ofstream outFile;

    outFile.open(fileName.c_str(), std::ios::app);

    if (outFile.fail()) {
        IO::println("Couldn't open output file");
        return;
    }

    outFile << message << endl << endl;

    outFile << "*                                       Ready Queue                                                                             Blocked Queue                                   *" << endl;
    outFile << "*********************************************************************************************************************************************************************************" << endl;
    outFile << "*           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED | TIME REMAINING* *           NAME          |   CLASS   | PRIORITY |  STATE  | SUSPENDED | TIME REMAINING*" << endl;
    outFile << "*-------------------------|-----------|----------|---------|-----------|---------------* *-------------------------|-----------|----------|---------|-----------|---------------*" << endl;

    PCB* pcbReady;
    PCB* pcbBlocked = mBlockedQueue.begin();

    for (pcbReady = mReadyQueue.cbegin(); pcbReady != mReadyQueue.cend(); pcbReady = pcbReady->getNext()) {

        if (pcbReady->getName().length() > 27) {
            outFile << "*" + pcbReady->getName().substr(0, 22) + "...|";
        } else {
            outFile << "*" + pcbReady->getName();

            for (int i = pcbReady->getName().length(); i < 25; i++) {
                outFile << " ";
            }

            outFile << "|";
        }

        if (pcbReady->getProcessClass() == SYSTEM) {
            outFile << "SYSTEM     |";
        } else {
            outFile << "APPLICATION|";
        }

        outFile << std::to_string(pcbReady->getPriority());

        for (int i = std::to_string(pcbReady->getPriority()).length(); i < 10; i++) {
            outFile << " ";
        }

        outFile << "|";

        if (pcbReady->getState() == READY) {
            outFile << "READY    |";
        } else {
            outFile << "BLOCKED  |";
        }

        if (pcbReady->getSuspend()) {
            outFile << "YES        |";
        } else {
            outFile << "NO         |";
        }

        outFile << std::to_string(pcbReady->getTimeRemaining());

        for (int i = std::to_string(pcbReady->getTimeRemaining()).length(); i < 15; i++) {
            outFile << " ";
        }

        outFile << "* ";


        if (pcbBlocked != mBlockedQueue.end()) {

            if (pcbBlocked->getName().length() > 27) {
                outFile << "*" + pcbBlocked->getName().substr(0, 22) + "...|";
            } else {
                outFile << "*" + pcbBlocked->getName();

                for (int i = pcbBlocked->getName().length(); i < 25; i++) {
                    outFile << " ";
                }

                outFile << "|";
            }

            if (pcbBlocked->getProcessClass() == SYSTEM) {
                outFile << "SYSTEM     |";
            } else {
                outFile << "APPLICATION|";
            }

            outFile << std::to_string(pcbBlocked->getPriority());

            for (int i = std::to_string(pcbBlocked->getPriority()).length(); i < 10; i++) {
                outFile << " ";
            }

            outFile << "|";

            if (pcbBlocked->getState() == READY) {
                outFile << "READY    |";
            } else {
                outFile << "BLOCKED  |";
            }

            if (pcbBlocked->getSuspend()) {
                outFile << "YES        |";
            } else {
                outFile << "NO         |";
            }

            outFile << std::to_string(pcbBlocked->getTimeRemaining());

            for (int i = std::to_string(pcbBlocked->getTimeRemaining()).length(); i < 15; i++) {
                outFile << " ";
            }
            pcbBlocked = pcbBlocked->getNext();
        } else {
            outFile << "*                                                                                      *";
        }

        outFile << endl;

    }

    outFile << "*********************************************************************************************************************************************************************************" << endl;

    outFile << endl;

    outFile.close();

}

int System::computeTurnaround(const vector<pcbTime> times) {

    int total = 0;

    for (int i = 0; i < times.size(); i++) {
        total =  total + (times.at(i).completionTime - times.at(i).arrivalTime);
    }

    if (times.size() == 0) {
        return -1;
    }

    return total / times.size();

}
