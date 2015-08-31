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

int TaskbarEventHandler::messageCallBack(Window *window, MessageQueue &msgQueue)
{
	int returnValue = 0;
	while (msgQueue.hasMessage())
	{
		switch (msgQueue.getMessage().controlID)
		{
		case TASKBAR:

			break;
		case POWER_BUTTON:
			switch (msgQueue.getMessage().messageID)
			{
			case LEFT_MOUSE_BUTTON_DOWN:
				returnValue = PowerButton_LeftDown((Button*)window, msgQueue);
				break;
			case LEFT_MOUSE_BUTTON_CLICK:
				returnValue = PowerButton_LeftClick((Button*)window, msgQueue);
				break;
			case LEFT_MOUSE_BUTTON_UP:
				returnValue = PowerButton_LeftUp((Button*)window, msgQueue);
				break;
			case MOUSE_ENTER:
				returnValue = PowerButton_MouseEnter((Button*)window, msgQueue);
				break;
			case MOUSE_LEAVE:
				returnValue = PowerButton_MouseLeave((Button*)window, msgQueue);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		msgQueue.removeMessage();
	}
	return returnValue;
}

int TaskbarEventHandler::PowerButton_LeftDown(Button *button, MessageQueue &msgQueue)
{
	button->setBackgroundColor(0, 0, 155, 180);
	return 0;
}

int TaskbarEventHandler::PowerButton_LeftClick(Button *button, MessageQueue &msgQueue)
{

	MessageWindow winMsg(500, 500, 500, 500, "Hi", "Test");

	winMsg.setWindowID(80);

	MessageWindowHandler handle;

	winMsg.setEventHandlerClass(&handle);

	Desktop *dp = dp->getInstance();

	dp->attachWindow(winMsg);

	return 0;
}

int TaskbarEventHandler::PowerButton_LeftUp(Button *button, MessageQueue &msgQueue)
{
	button->setBackgroundColor(0, 0, 155, 0);
	return 0;
}

int TaskbarEventHandler::PowerButton_MouseEnter(Button *button, MessageQueue &msgQueue)
{
	button->setOutlineThickness(1.5f);
	button->setOutlineColor(0, 0, 0, 255);
	button->setBackgroundColor(0, 0, 155, 0);
	return 0;
}

int TaskbarEventHandler::PowerButton_MouseLeave(Button *button, MessageQueue &msgQueue)
{
	button->setOutlineThickness(0.0f);
	button->setBackgroundColor(0, 0, 155, 0);
	return 0;
}