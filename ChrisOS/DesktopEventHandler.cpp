#include "DesktopEventHandler.h"
#include "System.h"

DesktopEventHandler::DesktopEventHandler()
{
}


DesktopEventHandler::~DesktopEventHandler()
{
}

int DesktopEventHandler::messageCallBack(Window *window, MessageQueue &messageQueue)
{
	static int xOffset;
		static int yOffset;
		static bool dragStarted;
	
		//MessageWindow mBox;
		while (messageQueue.hasMessage())
		{
			//switch (messageQueue.getMessage().messageID)
			//{
			//case LEFT_MOUSE_BUTTON_DOWN:
			//	switch (messageQueue.getMessage().controlID)
			//	{
			//	case 1:
			//		if (!dragStarted)
			//		{
			//			dragStarted = true;
			//		}
			//		else
			//		{
			//			window->setPosition(sf::Mouse::getPosition(System::getWindow()).x - xOffset, sf::Mouse::getPosition(System::getWindow()).y- yOffset);
			//		}
	
			//		xOffset = sf::Mouse::getPosition(System::getWindow()).x - window->getPosition().x;
			//		yOffset = sf::Mouse::getPosition(System::getWindow()).y - window->getPosition().y;
			//		break;
			//	case 3:
			//		window->setBackgroundColor(0, 0, 155, 120);
			//		break;
			//	default:
			//		break;
			//	}
			//	break;
			//case LEFT_MOUSE_BUTTON_UP:
			//	switch (messageQueue.getMessage().controlID)
			//	{
			//	case 1:
			//		dragStarted = false;
			//		break;
			//	case 3:
			//		window->setBackgroundColor(0, 0, 155, 0);
			//		break;
			//	default:
			//		break;
			//	}
			//	break;
			//case LEFT_MOUSE_BUTTON_CLICK:
			//	switch (messageQueue.getMessage().controlID)
			//	{
			//	case 1:
			//		Button_LeftClick(window, messageQueue);
			//		//window->setText("Please?!");
			//		break;
			//	case 2:
			//		//window->setString("I will cry");
			//		break;
			//	case 3:
			//		//mBox.show(500, 500, 250, 200, "Exit?");
			//		System::getWindow().close();
			//	default:
			//		break;
			//	}
			//	break;
			//case MOUSE_ENTER:
			//	if (messageQueue.getMessage().controlID == 1)
			//	{
			//		//window->setTextColor(sf::Color(0, 255, 0));
			//		//window->setBackgroundColor(sf::Color(51, 153, 255, 35));
			//		//window->setOutlineColor(sf::Color(51, 153, 255, 100));
			//	}
			//	if (messageQueue.getMessage().controlID == 2)
			//	{
			//		//window->setTextColor(sf::Color(255, 0, 255));
			//	}
			//	if (messageQueue.getMessage().controlID == 3)
			//	{
			//		//window->setOutlineColor(sf::Color(0, 0, 0));
			//		window->setOutlineThickness(1.0f);
			//	}
			//	break;
			//case MOUSE_LEAVE:
			//	switch (messageQueue.getMessage().controlID)
			//	{
			//	case 1:
			//		//window->setTextColor(sf::Color(0, 0, 0));
			//		//window->setBackgroundColor(sf::Color(120, 80, 180, 0));
			//		//window->setOutlineColor(sf::Color(120, 80, 130, 0));
			//		break;
			//	case 2:
			//		//window->setTextColor(sf::Color(0, 0, 0));
			//		break;
			//	case 3:
			//		window->setOutlineThickness(0.0f);
			//		window->setBackgroundColor(0, 0, 155, 0);
			//		break;
			//	default:
			//		break;
			//	}
			//default:
			//	break;
			//}
			messageQueue.removeMessage();
		}
		return 0;
}

int DesktopEventHandler::Button_LeftClick(Window *window, MessageQueue &msgQueue)
{
	Button *button = (Button*)window;

	button->setText("Please?!");
	return 0;
}