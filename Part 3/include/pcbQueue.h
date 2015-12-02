#ifndef PCBQUEUE_H_INCLUDED
#define PCBQUEUE_H_INCLUDED
#include "pcb.h"

class pcbQueue {

public:
    pcbQueue();
    ~pcbQueue();

    PCB* const cend() const;
    PCB* const cbegin() const;

    PCB* end() const;
    PCB* begin() const;

    void push_back(PCB* pcb);
    PCB* pop_front();

    bool remove(PCB* pcb);

    int numPCB();

    PCB* contains(std::string pcbName);

    bool isEmpty();

private:

    PCB* mHead;
    PCB* mTail;

    int numPCBs;

};

#endif // PCBQUEUE_H_INCLUDED
