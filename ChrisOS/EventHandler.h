#pragma once

#include "MessageQueue.h"

class Window;

class EventHandler
{
public:
	virtual void messageCallBack(Window *window, MessageQueue &messageQueue) = 0;
};