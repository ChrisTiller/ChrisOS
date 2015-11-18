#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "LinkedList.h"

template <class T>
class Queue {

private:

    void push_back(T data) {
        mList.insertAtEnd(data);
        numElements++;
    }

    T pop_front() {
        if (numElements) numElements--;

        return *mList.removeFromFront();
    }

    int size() {
        return numElements;
    }

private:
    LinkedList<T> mList;

    int numElements;
};

#endif // QUEUE_H_INCLUDED
