#pragma once

#include "EventHandler.h"

class MessageWindowHandler : public EventHandler
{
public:
	MessageWindowHandler();
	~MessageWindowHandler();

	void messageCallBack(Window *window, MessageQueue &msgQueue);
};

