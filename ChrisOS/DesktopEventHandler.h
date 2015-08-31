#pragma once

#include "EventHandler.h"
#include "Desktop.h"

class DesktopEventHandler : public EventHandler
{
public:
	DesktopEventHandler();
	~DesktopEventHandler();

	void messageCallBack(Window *window, MessageQueue &messageQueue);

	void Button_LeftClick(Window *window, MessageQueue &msgQueue);

private:

};

