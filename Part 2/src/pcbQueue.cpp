#include "pcbQueue.h"
#include <cassert>

pcbQueue::pcbQueue() : numPCBs(0) {

    mHead = new PCB();
    mTail = new PCB();

    mHead->setNext(mTail);
    mTail->setPrev(mHead);

}

pcbQueue::~pcbQueue() {

    PCB* curr = mHead->getNext();
    PCB* toDelete;

    while (curr != mTail) {
        toDelete = curr;
        curr = curr->getNext();
        delete toDelete;
    }

    delete mHead;
    delete mTail;

}

int pcbQueue::numPCB() {
    return numPCBs;
}

PCB* pcbQueue::cend() const {
    return mTail;
}

PCB* pcbQueue::contains(std::string pcbName) {
    // goes through all the PCBs in the queue to see if the specified process exists
    if (mHead->getNext() == mTail) {
        return NULL;
    }

    PCB* curr = mHead->getNext();

    while (curr != mTail) {
        if (curr->getName() == pcbName) {
            return curr;
        }
        curr = curr->getNext();
    }

    return NULL;
}

void pcbQueue::push_back(PCB* pcb) {

    assert(pcb != NULL);

    mTail->getPrev()->setNext(pcb);
    pcb->setPrev(mTail->getPrev());
    mTail->setPrev(pcb);
    pcb->setNext(mTail);

    numPCBs++;

}

PCB* pcbQueue::pop_front() {

    if (mHead->getNext() == mTail) {
        return NULL;
    }

    PCB* toRemove = mHead->getNext();

    mHead->setNext(toRemove->getNext());
    toRemove->getNext()->setPrev(mHead);

    numPCBs--;

    return toRemove;
}

PCB* pcbQueue::front() {

    if (mHead->getNext() == mTail) {
        return NULL;
    }

    return mHead->getNext();

}

bool pcbQueue::remove(PCB* pcb) {

    assert(pcb != NULL);

    PCB* toRemove = contains(pcb->getName());

    if (toRemove != NULL) {

        toRemove->getPrev()->setNext(toRemove->getNext());
        toRemove->getNext()->setPrev(toRemove->getPrev());
        numPCBs--;

        return true;
    }
    return false;
}
