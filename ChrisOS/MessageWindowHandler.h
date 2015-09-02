#pragma once

#include "EventHandler.h"
#include "MessageWindow.h"
class Button;

class MessageWindowHandler : public EventHandler
{
public:
	MessageWindowHandler();
	~MessageWindowHandler();

	int messageCallBack(Window *parent, Window *child, MessageQueue &msgQueue);


	int ButtonOK_LeftClick(MessageWindow *parent, Button *button, MessageQueue &msgQueue);
	int ButtonOK_MouseEner(MessageWindow *parent, Button *button, MessageQueue &msgQueue);
	int ButtonOK_MouseLeave(MessageWindow *parent, Button *button, MessageQueue &msgQueue);
	int ButtonCancel_LeftClick(MessageWindow *parent, Button *button, MessageQueue &msgQueue);
};

