#ifndef PCB_H_INCLUDED
#define PCB_H_INCLUDED

#include <string>

using std::string;

enum PROCESS_CLASS {
    SYSTEM,
    APPLICATION
}

enum STATE {
    RUNNING,
    READY,
    BLOCKED
}

enum PROCESS_ERROR {
    PROCESS_ALLOCATION_FAILED,
    PROCESS_NOT_ALLOCATED,
    PROCESS_ALREADY_EXISTS,
 }

typedef signed char int8;

class PCB {

public:

    PCB(string name, PROCESS_CLASS processClass, int8 processPriority);

private:
    string mProcessName;
    PROCESS_CLASS mProcessClass;
    int8 mProcessPriority;
    STATE mProcessState;
    int mProcessMemory;

};

#endif // PCB_H_INCLUDED
