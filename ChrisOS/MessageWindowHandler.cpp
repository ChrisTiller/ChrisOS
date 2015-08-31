#include "MessageWindowHandler.h"
#include "Button.h"

MessageWindowHandler::MessageWindowHandler()
{
}


MessageWindowHandler::~MessageWindowHandler()
{
}

int MessageWindowHandler::messageCallBack(Window *window, MessageQueue &msgQueue)
{
	int returnValue = 0;
	while (msgQueue.hasMessage())
	{
		switch (msgQueue.getMessage().controlID)
		{
		case BUTTON_OK:
			switch (msgQueue.getMessage().messageID)
			{
			case LEFT_MOUSE_BUTTON_CLICK:
				returnValue = ButtonOK_LeftClick((Button*)window, msgQueue);
				break;
			default:
				break;
			}
			break;
		case BUTTON_CANCEL:
			switch (msgQueue.getMessage().messageID)
			{
			case LEFT_MOUSE_BUTTON_CLICK:
				returnValue = ButtonCancel_LeftClick((Button*)window, msgQueue);
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


int MessageWindowHandler::ButtonOK_LeftClick(Button *button, MessageQueue &msgQueue)
{
	return BUTTON_OK;
}

int MessageWindowHandler::ButtonCancel_LeftClick(Button *button, MessageQueue &msgQueue)
{
	return BUTTON_CANCEL;
}