#include "../include/system.h"

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
    //return getDate(vector<string>(params.begin(), params.begin() + 1)) + " " + getTime(vector<string>(params.begin() + 1, params.begin() + 2));
}
