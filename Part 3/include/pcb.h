#ifndef PCB_H_INCLUDED
#define PCB_H_INCLUDED

#include <string>

using std::string;

enum PROCESS_CLASS {
    SYSTEM,
    APPLICATION
};

enum STATE {
    RUNNING,
    READY,
    BLOCKED
};

enum PROCESS_ERROR {
    PROCESS_ALLOCATION_FAILED,
    PROCESS_NOT_ALLOCATED,
    PROCESS_ALREADY_EXISTS
 };

class PCB {

public:
    PCB() :
        mNext(NULL),
        mPrev(NULL),
        mProcessName(""),
        mProcessClass(SYSTEM),
        mProcessPriority(0),
        mProcessState(READY),
        mProcessMemory(0),
        mTimeRemaining(0)
    {}
    PCB(string name, PROCESS_CLASS processClass, int processPriority);

    PCB* getNext() { return mNext; }
    PCB* getPrev() { return mPrev; }

    void setNext(PCB* pcb) { mNext = pcb; }
    void setPrev(PCB* pcb) { mPrev = pcb; }

    string getName() { return mProcessName; }
    void setName(string name) { mProcessName = name; }

    PROCESS_CLASS getProcessClass() { return mProcessClass; }
    void setProcessClass(PROCESS_CLASS processClass) { mProcessClass = processClass; }

    int getPriority() { return mProcessPriority; }
    void setPrioirty(int value) { mProcessPriority = value; }

    STATE getState() { return mProcessState; }
    void setState(STATE state) { mProcessState = state; }

    void setMemory(int memory) { mProcessMemory = memory; }
    int getMemory() { return mProcessMemory; }

    void setSuspend(bool suspend) { mSuspend = suspend; }
    bool getSuspend() { return mSuspend; }

    void setTimeRemaining(int timeRemaining) { mTimeRemaining = timeRemaining; }
    bool getTimeRemaining() { return mTimeRemaining; }

private:
    string mProcessName;
    PROCESS_CLASS mProcessClass;
    int mProcessPriority;
    STATE mProcessState;
    int mProcessMemory;
    bool mSuspend;
    int mTimeRemaining;

    PCB* mNext;
    PCB* mPrev;

};

#endif // PCB_H_INCLUDED
