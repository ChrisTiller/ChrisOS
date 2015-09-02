#pragma once

#include "MessageQueue.h"

class Window;

class EventHandler
{
public:
	virtual int messageCallBack(Window *parent, Window *child, MessageQueue &messageQueue) = 0;
};