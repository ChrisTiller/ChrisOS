#include "Node.h"



Node::Node() : mData(0), mNext(nullptr), mPrev(nullptr) {
}

Node::Node(int value) : mData(value), mPrev(nullptr), mNext(nullptr) {
}

Node::Node(int value, Node* prev, Node* next) : mData(value), mPrev(prev), mNext(next) {
}


Node::~Node() {
	mPrev = nullptr;
	mNext = nullptr;
}

int Node::getValue() {
	return mData;
}

void Node::setValue(int value) {
	if (this != nullptr) {
		mData = value;
	}
}

Node * Node::getNext() {
	return mNext;
}

Node * Node::getPrev() {
	return mPrev;
}

void Node::setNext(Node * next) {
	if (this != nullptr) {
		mNext = next;
	}
}

void Node::setPrev(Node * prev) {
	if (this != nullptr) {
		mPrev = prev;
	}
}
