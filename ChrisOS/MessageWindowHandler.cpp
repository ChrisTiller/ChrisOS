#include "MessageWindowHandler.h"
#include "Button.h"

MessageWindowHandler::MessageWindowHandler()
{
}


MessageWindowHandler::~MessageWindowHandler()
{
}

int MessageWindowHandler::messageCallBack(Window *parent, Window *child, MessageQueue &msgQueue)
{
	int returnValue = 0;
	while (msgQueue.hasMessage())
	{
		switch (msgQueue.getMessage().controlID)
		{
		case BUTTON_OK:
			switch (msgQueue.getMessage().messageID)
			{
			case MOUSE_ENTER:
				returnValue = ButtonOK_MouseEner(static_cast<MessageWindow*>(parent), static_cast<Button*>(child), msgQueue);
				break;
			case MOUSE_LEAVE:
				returnValue = ButtonOK_MouseEner(static_cast<MessageWindow*>(parent), static_cast<Button*>(child), msgQueue);
				break;
			case LEFT_MOUSE_BUTTON_CLICK:
				returnValue = ButtonOK_LeftClick(static_cast<MessageWindow*>(parent), static_cast<Button*>(child), msgQueue);
				break;
			default:
				break;
			}
			break;
		case BUTTON_CANCEL:
			switch (msgQueue.getMessage().messageID)
			{
			case LEFT_MOUSE_BUTTON_CLICK:
				returnValue = ButtonCancel_LeftClick(static_cast<MessageWindow*>(parent), static_cast<Button*>(child), msgQueue);
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


int MessageWindowHandler::ButtonOK_LeftClick(MessageWindow *parent, Button *button, MessageQueue &msgQueue)
{
	parent->close();
	return BUTTON_OK;
}

int MessageWindowHandler::ButtonOK_MouseEner(MessageWindow *parent, Button *button, MessageQueue &msgQueue)
{
	button->setFont("Oswald-Light.ttf", 25.0f);
	button->setText("OK");
	return 0;
}
int MessageWindowHandler::ButtonOK_MouseLeave(MessageWindow *parent, Button *button, MessageQueue &msgQueue)
{
	button->setFont("Oswald-Light.ttf", 25.0f);
	button->setText("OK");
	return 0;
}

int MessageWindowHandler::ButtonCancel_LeftClick(MessageWindow *parent, Button *button, MessageQueue &msgQueue)
{
	return BUTTON_CANCEL;
}