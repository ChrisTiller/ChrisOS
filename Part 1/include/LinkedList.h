#pragma once
#include "Node.h"

class LinkedList {
public:
	LinkedList();
	~LinkedList();

	int at(int position);
	void clear();
	bool empty();
	void erase(int position);
	int getValue();
	void insertAtEnd(int value);
	void insertAtBeginning(int value);
	void insertAfter(int position, int value);
	void insertBefore(int position, int value);
	void moveToHead();
	void moveToTail();
	void moveNext();
	void movePrev();
	int size();

	Node* getHead();
	Node* getCurrent();
	Node* getTail();

private:

	void connectNodes(Node* before, Node* current, Node* after);
	void connectNodes(Node* before, Node* after);

	Node* nodeFromPosition(int position);

	Node* mHead;
	Node* mTail;
	Node* current;
	int mNodes;
};

