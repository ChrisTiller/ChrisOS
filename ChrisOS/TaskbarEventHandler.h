#pragma once

#include "EventHandler.h"

class Button;

class TaskbarEventHandler : public EventHandler
{
public:
	TaskbarEventHandler();
	~TaskbarEventHandler();

	void messageCallBack(Window* window, MessageQueue &messageQueue);

	void PowerButton_LeftClick(Button *button, MessageQueue &msgQueue);
	void PowerButton_LeftUp(Button *button, MessageQueue &msgQueue);
	void PowerButton_LeftDown(Button *button, MessageQueue &msgQueue);
	void PowerButton_MouseEnter(Button *button, MessageQueue &msgQueue);
	void PowerButton_MouseLeave(Button *button, MessageQueue &msgQueue);

private:

};

