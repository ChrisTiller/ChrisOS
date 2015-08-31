#pragma once

#include "EventHandler.h"
#include "MessageWindow.h"
class Button;

class MessageWindowHandler : public EventHandler
{
public:
	MessageWindowHandler();
	~MessageWindowHandler();

	int messageCallBack(Window *window, MessageQueue &msgQueue);

	int ButtonOK_LeftClick(Button *button, MessageQueue &msgQueue);
	int ButtonCancel_LeftClick(Button *button, MessageQueue &msgQueue);
};

