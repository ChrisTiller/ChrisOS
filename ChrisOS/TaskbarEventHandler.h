#pragma once

#include "EventHandler.h"

class Button;

class TaskbarEventHandler : public EventHandler
{
public:
	TaskbarEventHandler();
	~TaskbarEventHandler();

	int messageCallBack(Window *parent, Window *child, MessageQueue &messageQueue);

	int PowerButton_LeftClick(Window *parent, Button *button, MessageQueue &msgQueue);
	int PowerButton_LeftDown(Window *parent, Button *button, MessageQueue &msgQueue);
	int PowerButton_LeftUp(Window *parent, Button *button, MessageQueue &msgQueue);
	int PowerButton_MouseEnter(Window *parent, Button *button, MessageQueue &msgQueue);
	int PowerButton_MouseLeave(Window *parent, Button *button, MessageQueue &msgQueue);

private:

};

