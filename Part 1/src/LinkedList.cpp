#include "LinkedList.h"

LinkedList::LinkedList() : mNodes(0), mHead(nullptr), mTail(nullptr) {
}


LinkedList::~LinkedList() {
	clear();
}

void LinkedList::clear() {
	if (mHead == nullptr) {
		return;
	}

	Node* currentNode = mHead;
	Node* nodeToErase;

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
	if (mHead == nullptr) {
		return true;
	}
	return false;
}

void LinkedList::erase(int position) {
	if ((mHead == nullptr) || (position < 0) || (position > mNodes)) {
		return;
	}
	
	Node* nodeToErase = nodeFromPosition(position);

	if (nodeToErase == mHead) {
		mHead = mHead->getNext();
	}

	if (nodeToErase == mTail) {
		mTail = mTail->getPrev();
	}

	connectNodes(nodeToErase->getPrev(), nodeToErase->getNext());

	nodeToErase->setNext(nullptr);
	nodeToErase->setPrev(nullptr);
	delete nodeToErase;
	mNodes--;

	moveToHead();
}

int LinkedList::getValue() {
	return current->getValue();
}

int LinkedList::at(int position) {
	if ((mHead == nullptr) || (position < 0) || (position > mNodes)) {
		return 0;
	}

	return nodeFromPosition(position)->getValue();
}

void LinkedList::insertAtEnd(int value) {
	if (mNodes == 0) {
		insertAfter(mNodes, value);
	}
	else {
		insertAfter(mNodes - 1, value);
	}

	if (mNodes > 1) {
		mTail = mTail->getNext();
	}

	moveToHead();
}

void LinkedList::insertAtBeginning(int value) {
	insertBefore(0, value);

	if (mNodes > 1) {
		mHead = mHead->getPrev();
	}

	moveToHead();
}

void LinkedList::insertAfter(int position, int value) {

	if ((position < 0) || (position > mNodes)) {
		return;
	}
	
	if (mHead == nullptr) {
		mHead = new Node(value);
		mTail = mHead;
	} else {
		Node* newNode = new Node(value);
		Node* currentNode = nodeFromPosition(position);
		
		connectNodes(currentNode, newNode, currentNode->getNext());
	}
	mNodes++;
	moveToHead();
}

void LinkedList::insertBefore(int position, int value) {

	if ((position < 0) || (position > mNodes)) {
		return;
	}

	if (mHead == nullptr) {
		mHead = new Node(value);
		mTail = mHead;
	} else {
		Node* newNode = new Node(value);
		Node* currentNode = nodeFromPosition(position);
		
		connectNodes(currentNode->getPrev(), newNode, currentNode);
	}
	mNodes++;
	moveToHead();
}

void LinkedList::moveToHead() {
	current = mHead;
}

void LinkedList::moveToTail() {
	current = mTail;
}

void LinkedList::moveNext() {
	if (current != mTail) {
		current = current->getNext();
	}
}

void LinkedList::movePrev() {
	if (current != mHead) {
		current = current->getPrev();
	}
}

int LinkedList::size() {
	return mNodes;
}

Node * LinkedList::getHead() {
	return mHead;
}

Node * LinkedList::getCurrent() {
	return current;
}

Node * LinkedList::getTail() {
	return mTail;
}

void LinkedList::connectNodes(Node * before, Node * current, Node * after) {
	if (before != nullptr) {
		before->setNext(current);
	}
	current->setPrev(before);
	current->setNext(after);
	if (after != nullptr) {
		after->setPrev(current);
	}
}

void LinkedList::connectNodes(Node * before, Node * after) {
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

	Node* currentNode = mHead;
	int i = 0;

	while (i++ < position) {
		currentNode = currentNode->getNext();
	}

	return currentNode;
}