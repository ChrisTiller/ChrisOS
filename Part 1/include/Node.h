#pragma once

class Node {
public:
	Node();
	Node(int value);
	Node(int value, Node* prev, Node* next);
	~Node();

	Node* getNext();
	Node* getPrev();
	int getValue();
	void setNext(Node*);
	void setPrev(Node*);
	void setValue(int);

private:
	Node* mNext;
	Node* mPrev;
	int mData;
};

