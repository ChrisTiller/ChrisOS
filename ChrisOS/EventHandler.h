#pragma once

#include "MessageQueue.h"

class Window;

class EventHandler
{
public:
	virtual int messageCallBack(Window *window, MessageQueue &messageQueue) = 0;
};