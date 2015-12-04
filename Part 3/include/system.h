#ifndef _SYSTEM_H_INCLUDED_
#define _SYSTEM_H_INCLUDED_

#include <cstdlib>
#include <ctime>
#include <string>
#include <map>
#include <curses.h>

#include "io.h"
#include "command.h"
#include "pcbQueue.h"

#ifndef NULL
#define NULL 0
#endif // NULL

using std::map;

class System {

public:
    static System* getInstance();

    void init();
    void close();
    void systemLoop();

    void alias(const vector<string>& params);
    void createPCB(const vector<string>& params);
    void deletePCB(const vector<string>& params);
    void block(const vector<string>& params);
    void unblock(const vector<string>& params);
    void suspend(const vector<string>& params);
    void resume(const vector<string>& params);
    void setPriority(const vector<string>& params);
    void showPCB(const vector<string>& params);
    void showAll(const vector<string>& params);
    void showReady(const vector<string>& params);
    void showBlocked(const vector<string>& params);

    void SJF(const vector<string>& params);
    void FIFO(const vector<string>& params);
    void STCF(const vector<string>& params);
    void FPPS(const vector<string>& params);
    void RR(const vector<string>& params);
    void MLFQ(const vector<string>& params);

    void getDateTime(const vector<string>& params);
    void getTime(const vector<string>& params);
    void getDate(const vector<string>& params);
    void getVersion(const vector<string>& params);

    void help(const vector<string>& params);

private:
    System() {
        //initscr();
        //mWidth = COLS;
        //mHeight = LINES;
        //endwin();

        loadSystemFunctions();
    };

    static System* mInstance;

    System (System const&) = delete;
    void operator=(System const&) = delete;

    void loadSystemFunctions();
    void loadJobs(const vector<string>& params, pcbQueue& jobQueue);

    bool findCommand(Command& command);

    PCB* allocatePCB();
    void freePCB(PCB* pcb);
    PCB* setupPCB(string name, int priority, PROCESS_CLASS processClass);
    PCB* findPCB(string name);

    void insertPCB(PCB* pcb);
    bool removePCB(PCB* pcb);

    void displayPCBInfo(PCB* pcb);

    void displayQueueInfo(string fileName, string message);

    struct pcbTime {
        int completionTime = 0;
        int arrivalTime = 0;
    };

    int computeTurnaround(const vector<pcbTime> times);

    int mWidth;
    int mHeight;

    typedef void (System::*systemFunction)(const vector<string>&);

    map<string, systemFunction> systemFunctions;
    map<string, string> aliasCommands;

    pcbQueue mReadyQueue;
    pcbQueue mBlockedQueue;

};


#endif
