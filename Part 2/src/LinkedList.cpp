#include "LinkedList.h"
#include <cassert>

LinkedList::LinkedList() : mNodes(0) {

    mHead = mTail = new PCB;

}


LinkedList::~LinkedList() {
	clear();
}

void LinkedList::clear() {
	if (mHead == mTail) {
		return;
	}

	PCB* currentNode = mHead;
	PCB* nodeToErase;

	while (currentNode != nullptr) {
		nodeToErase = currentNode;
		currentNode = currentNode->getNext();
		nodeToErase->setPrev(nullptr);
		nodeToErase->setNext(nullptr);
		delete nodeToErase;
		mNodes--;
	}
}

bool LinkedList::empty() {
	if (mHead == mTail) {
		return true;
	}
	return false;
}

void LinkedList::erase(PCB* pcb) {
	if ((mHead == mTail)) {
		return;
	}

	assert(pcb != NULL);

	PCB* pcbToErase = mHead->getNext();

	while (pcbToErase != pcb) {
        pcbToErase = pcbToErase->getNext();
	}

	connectNodes(nodeToErase->getPrev(), nodeToErase->getNext());

	nodeToErase->setNext(nullptr);
	nodeToErase->setPrev(nullptr);
	delete nodeToErase;
	mNodes--;
}
/*
PCB* LinkedList::at(int position) {
	if ((mHead == mTail) || (position < 0) || (position > mNodes)) {
		return 0;
	}

	return nodeFromPosition(position);
}

void LinkedList::insertAtEnd(string name, PROCESS_CLASS processClass, int processPriority) {
	if (mNodes == 0) {
		insertAfter(mNodes, value);
	}
	else {
		insertAfter(mNodes - 1, value);
	}

	if (mNodes > 1) {
		mTail = mTail->getNext();
	}

}

void LinkedList::insertAtBeginning(string name, PROCESS_CLASS processClass, int processPriority) {
	insertBefore(0, value);

	if (mNodes > 1) {
		mHead = mHead->getPrev();
	}
}

void LinkedList::insertAfter(int position, string name, PROCESS_CLASS processClass, int processPriority) {

	if ((position < 0) || (position > mNodes)) {
		return;
	}

	if (mHead == nullptr) {
		mHead = new PCB(name, processClass, processPriority);
		mTail = mHead;
	} else {
		PCB* newNode = new PCB(name, processClass, processPriority);
		PCB* currentNode = nodeFromPosition(position);

		connectNodes(currentNode, newNode, currentNode->getNext());
	}
	mNodes++;
}

void LinkedList::insertBefore(int position, string name, PROCESS_CLASS processClass, int processPriority) {

	if ((position < 0) || (position > mNodes)) {
		return;
	}

	if (mHead == nullptr) {
		mHead = new PCB(name, processClass, processPriority);
		mTail = mHead;
	} else {
		PCB* newNode = new PCB(name, processClass, processPriority);
		PCB* currentNode = nodeFromPosition(position);

		connectNodes(currentNode->getPrev(), newNode, currentNode);
	}
	mNodes++;
}
*/
int LinkedList::size() {
	return mNodes;
}

void LinkedList::connectNodes(PCB * before, PCB * current, PCB * after) {
	if (before != nullptr) {
		before->setNext(current);
	}
	current->setPrev(before);
	current->setNext(after);
	if (after != nullptr) {
		after->setPrev(current);
	}
}

void LinkedList::connectNodes(PCB * before, PCB * after) {
	if (before != nullptr) {
		before->setNext(after);
	}

	if (after != nullptr) {
		after->setPrev(before);
	}
}

Node * LinkedList::nodeFromPosition(int position) {

	if (position == 0) {
		return mHead;
	}

	if (position == mNodes) {
		return mTail;
	}

	PCB* currentNode = mHead;
	int i = 0;

	while (i++ < position) {
		currentNode = currentNode->getNext();
	}

	return currentNode;
}
