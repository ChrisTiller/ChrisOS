#pragma once

#include "EventHandler.h"
#include "Desktop.h"

class Button;

class DesktopEventHandler : public EventHandler
{
public:
	DesktopEventHandler();
	~DesktopEventHandler();

	int messageCallBack(Window *parent, Window *child, MessageQueue &msgQueue);

	int Button_LeftClick(Window *window, Button *button, MessageQueue &msgQueue);

private:

};

