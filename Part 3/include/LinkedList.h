#ifndef _LINKEDLIST_H_INCLUDED_
#define _LINKEDLIST_H_INCLUDED_
#include "pcb.h"

class LinkedList {
public:
	LinkedList();
	~LinkedList();

	//PCB* at(int position);
	PCB* removeFromFront();
	void clear();
	bool empty();
	void erase(PCB* pcb);
	void insert(PCB* pcb);
	//void insertAtEnd(string name, PROCESS_CLASS processClass, int processPriority);
	//void insertAtBeginning(string name, PROCESS_CLASS processClass, int processPriority);
	//void insertAfter(int position, string name, PROCESS_CLASS processClass, int processPriority);
	//void insertBefore(int position, string name, PROCESS_CLASS processClass, int processPriority);
	int size();

private:

	void connectNodes(PCB* before, PCB* current, PCB* after);
	void connectNodes(PCB* before, PCB* after);

	PCB* nodeFromPosition(int position);

	PCB* mHead;
	PCB* mTail;
	PCB* current;
	int mNodes;
};

#endif
