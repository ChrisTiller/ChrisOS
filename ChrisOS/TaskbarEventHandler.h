#pragma once

#include "EventHandler.h"

class Button;

class TaskbarEventHandler : public EventHandler
{
public:
	TaskbarEventHandler();
	~TaskbarEventHandler();

	int messageCallBack(Window* window, MessageQueue &messageQueue);

	int PowerButton_LeftClick(Button *button, MessageQueue &msgQueue);
	int PowerButton_LeftDown(Button *button, MessageQueue &msgQueue);
	int PowerButton_LeftUp(Button *button, MessageQueue &msgQueue);
	int PowerButton_MouseEnter(Button *button, MessageQueue &msgQueue);
	int PowerButton_MouseLeave(Button *button, MessageQueue &msgQueue);

private:

};

