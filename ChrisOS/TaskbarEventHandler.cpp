#include "TaskbarEventHandler.h"
#include "Taskbar.h"
#include "System.h"

TaskbarEventHandler::TaskbarEventHandler()
{
}

TaskbarEventHandler::~TaskbarEventHandler()
{
}

void TaskbarEventHandler::messageCallBack(Window *window, MessageQueue &msgQueue)
{
	while (msgQueue.hasMessage())
	{
		switch (msgQueue.getMessage().controlID)
		{
		case POWER_BUTTON:
			switch (msgQueue.getMessage().messageID)
			{
			case LEFT_MOUSE_BUTTON_DOWN:
				PowerButton_LeftDown((Button*)window, msgQueue);
				break;
			case LEFT_MOUSE_BUTTON_CLICK:
				PowerButton_LeftClick((Button*)window, msgQueue);
				break;
			case LEFT_MOUSE_BUTTON_UP:
				PowerButton_LeftUp((Button*)window, msgQueue);
				break;
			case MOUSE_ENTER:
				PowerButton_MouseEnter((Button*)window, msgQueue);
				break;
			case MOUSE_LEAVE:
				PowerButton_MouseLeave((Button*)window, msgQueue);
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
}

void TaskbarEventHandler::PowerButton_LeftDown(Button *button, MessageQueue &msgQueue)
{
	button->setBackgroundColor(0, 0, 155, 180);
}

void TaskbarEventHandler::PowerButton_LeftClick(Button *button, MessageQueue &msgQueue)
{
	System::getWindow().close();
}

void TaskbarEventHandler::PowerButton_LeftUp(Button *button, MessageQueue &msgQueue)
{
	button->setBackgroundColor(0, 0, 155, 0);
}

void TaskbarEventHandler::PowerButton_MouseEnter(Button *button, MessageQueue &msgQueue)
{
	button->setOutlineThickness(1.5f);
	button->setOutlineColor(0, 0, 0, 255);
	button->setBackgroundColor(0, 0, 155, 0);
}

void TaskbarEventHandler::PowerButton_MouseLeave(Button *button, MessageQueue &msgQueue)
{
	button->setOutlineThickness(0.0f);
	button->setBackgroundColor(0, 0, 155, 0);
}