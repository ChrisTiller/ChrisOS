#include "TaskbarEventHandler.h"
#include "Taskbar.h"
#include "System.h"
#include "MessageWindow.h"
#include "MessageWindowHandler.h"

TaskbarEventHandler::TaskbarEventHandler()
{
}

TaskbarEventHandler::~TaskbarEventHandler()
{
}

int TaskbarEventHandler::messageCallBack(Window *parent, Window *child, MessageQueue &msgQueue)
{
	int returnValue = 0;
	while (msgQueue.hasMessage())
	{
		bool handled = false;
		switch (msgQueue.getMessage().controlID)
		{
		case TASKBAR:
			break;
		case POWER_BUTTON:
			switch (msgQueue.getMessage().messageID)
			{
			case LEFT_MOUSE_BUTTON_DOWN:
				handled = true;
				returnValue = PowerButton_LeftDown(parent, static_cast<Button*>(child), msgQueue);
				break;
			case LEFT_MOUSE_BUTTON_CLICK:
				handled = true;
				returnValue = PowerButton_LeftClick(parent, static_cast<Button*>(child), msgQueue);
				break;
			case LEFT_MOUSE_BUTTON_UP:
				handled = true;
				returnValue = PowerButton_LeftUp(parent, static_cast<Button*>(child), msgQueue);
				break;
			case MOUSE_ENTER:
				handled = true;
				returnValue = PowerButton_MouseEnter(parent, static_cast<Button*>(child), msgQueue);
				break;
			case MOUSE_LEAVE:
				handled = true;
				returnValue = PowerButton_MouseLeave(parent, static_cast<Button*>(child), msgQueue);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		if (!handled)
		{
			msgQueue.removeMessage();
		}
	}
	return returnValue;
}

int TaskbarEventHandler::PowerButton_LeftDown(Window *parent, Button *button, MessageQueue &msgQueue)
{
	msgQueue.removeMessage();
	button->setBackgroundColor(0, 0, 155, 180);
	return 0;
}

int TaskbarEventHandler::PowerButton_LeftClick(Window *parent, Button *button, MessageQueue &msgQueue)
{
	msgQueue.removeMessage();

	MessageWindow winMsg(500, 500, 500, 500, "Hi", "Test");

	winMsg.setWindowID(100);

	MessageWindowHandler handle;

	winMsg.setEventHandlerClass(&handle);

	Desktop *dp = dp->getInstance();

	dp->attachWindow(winMsg);

	while (winMsg.isOpen())
	{
		System::doEvents();
	}

	System::getWindow().close();

	return 0;
}

int TaskbarEventHandler::PowerButton_LeftUp(Window *parent, Button *button, MessageQueue &msgQueue)
{
	msgQueue.removeMessage();
	button->setBackgroundColor(0, 0, 155, 0);
	return 0;
}

int TaskbarEventHandler::PowerButton_MouseEnter(Window *parent, Button *button, MessageQueue &msgQueue)
{
	msgQueue.removeMessage();
	button->setOutlineThickness(1.5f);
	button->setOutlineColor(0, 0, 0, 255);
	button->setBackgroundColor(0, 0, 155, 0);
	return 0;
}

int TaskbarEventHandler::PowerButton_MouseLeave(Window *parent, Button *button, MessageQueue &msgQueue)
{
	msgQueue.removeMessage();
	button->setOutlineThickness(0.0f);
	button->setBackgroundColor(0, 0, 155, 0);
	return 0;
}