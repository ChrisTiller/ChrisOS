#ifndef PCBQUEUE_H_INCLUDED
#define PCBQUEUE_H_INCLUDED
#include "pcb.h"

class pcbQueue {

public:
    pcbQueue();
    ~pcbQueue();

    PCB* cend() const;

    void push_back(PCB* pcb);
    PCB* pop_front();
    PCB* front();

    bool remove(PCB* pcb);

    int numPCB();

    PCB* contains(std::string pcbName);

private:

    PCB* mHead;
    PCB* mTail;

    int numPCBs;

};

#endif // PCBQUEUE_H_INCLUDED
