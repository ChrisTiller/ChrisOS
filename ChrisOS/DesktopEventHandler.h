#pragma once

#include "EventHandler.h"
#include "Desktop.h"

class DesktopEventHandler : public EventHandler
{
public:
	DesktopEventHandler();
	~DesktopEventHandler();

	int messageCallBack(Window *window, MessageQueue &messageQueue);

	int Button_LeftClick(Window *window, MessageQueue &msgQueue);

private:

};

