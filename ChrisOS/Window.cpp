#include "Window.h"
#include "System.h"

Window::Window() :
	mEventHandlerClass(nullptr),
	mWindowID(0),
	mNumWindows(0),
	mBackgroundColor(255, 255, 255, 255),
	mOutlineColor(0, 0, 0, 255),
	mBody({ 0.0f, 0.0f }),
	mSize(0.0f, 0.0f)
{
}

Window::Window(const sf::Vector2f size)
{
	setSize(size.x, size.y);
}

Window::Window(const float x, const float y)
{
	setSize(x, y);
}

Window::Window(const sf::Uint32 windowID, const sf::Vector2f size, EventHandler *eventHandlerClass) :
	mEventHandlerClass(eventHandlerClass),
	mWindowID(windowID),
	mNumWindows(0),
	mBackgroundColor(255, 255, 255, 255),
	mOutlineColor(0, 0, 0, 255)
{
	setSize(size.x, size.y);
}

Window::~Window()
{
	for (int i = 0; i < mChildren.size(); i++)
	{
		//delete mChildren.at(i);
	}

	mEventHandlerClass = nullptr;
}

void Window::attachWindow(Window &window)
{
	if (window.getWindowID() == 0)
	{
		return;
	}
	for (int i = 0; i < mChildren.size(); i++)
	{
		if (mChildren.at(i)->getWindowID() == window.getWindowID())
		{
			return;
		}
	}

	window.setParent(*this);
	if (!window.getEventHandler())
	{
		window.setEventHandlerClass(mEventHandlerClass);
	}
	mChildren.push_back(&window);
	mNumWindows++;
}

sf::Vector2f& Window::getSize()
{
	return sf::Vector2f(mSize.x, mSize.y);
}

Window* Window::getParent()
{
	return mParent;
}

sf::Uint32 Window::getWindowID()
{
	return mWindowID;
}

sf::Vector2f Window::getWindowPosition()
{
	return sf::Vector2f(mBody.getLocalBounds().left, mBody.getLocalBounds().height);
}

sf::FloatRect Window::getWindowRect()
{
	return sf::FloatRect(getPosition().x, getPosition().y, mSize.x, mSize.y);
}

EventHandler *Window::getEventHandler()
{
	return mEventHandlerClass;
}

void Window::sendMessage(uint controlID, uint message, sf::Event &event)
{
	mWindowMsgQueue.addMessage(controlID, message, event);
}

void Window::setBackgroundColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha)
{
	mBackgroundColor = sf::Color(red, green, blue, alpha);
	mBody.setFillColor(sf::Color(red, green, blue, alpha));
}

void Window::setEventHandlerClass(EventHandler *eventHandlerClass)
{
	mEventHandlerClass = eventHandlerClass;

	for (int i = 0; i < mChildren.size(); i++)
	{
		if (!mChildren.at(i)->getEventHandler())
		{ 
			mChildren.at(i)->setEventHandlerClass(eventHandlerClass);
		}
	}
}

void Window::setOutlineColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha)
{
	mOutlineColor = sf::Color(red, green, blue, alpha);
	mBody.setOutlineColor(sf::Color(red, green, blue, alpha));
}

void Window::setOutlineThickness(float thickness)
{
	mBody.setOutlineThickness(thickness);
}

void Window::setParent(Window &window)
{
	mParent = &window;
}

void Window::setSize(sf::Vector2f size)
{
	setSize(size.x, size.y);
}

void Window::setSize(const float x, const float y)
{
	sf::Vector2f newSize = sf::Vector2f(x / System::getInternalResolution().x * System::getWindow().getSize().x, y / System::getInternalResolution().y * System::getWindow().getSize().y);
	mSize = newSize;
	mBody = sf::RectangleShape(newSize);
}

void Window::setWindowPosition(const float x, const float y)
{
	sf::Vector2f newSize = sf::Vector2f(x / System::getInternalResolution().x * System::getWindow().getSize().x, y / System::getInternalResolution().y * System::getWindow().getSize().y);
	setPosition(newSize.x, newSize.y);
}

void Window::setWindowID(sf::Uint32 ID)
{
	mWindowID = ID;
}

void Window::setWindowPosition(const sf::Vector2f size)
{
	setWindowPosition(size.x, size.y);
}

void Window::drawMe(sf::RenderTarget &target, sf::RenderStates states) const
{
	draw(target, states);
}

void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBody, states);

	for (int i = 0; i < mZOrderChildren.size(); i++)
	{
		mChildren.at(i)->draw(target, states);
	}
}

int Window::events(sf::Event &event, sf::RenderWindow &window)
{
	sf::FloatRect body = getWindowRect();

	if (getWindowID() == 0 && mParent != nullptr)
	{
		return 0;
	}

	mMouseOver = false;
	sf::Vector2f mouseCoords(sf::Mouse::getPosition(System::getWindow()));
	if (body.contains(mouseCoords))
	{
		mMouseOver = true;
	}

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (mMouseOver) {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				mWindowMsgQueue.addMessage(getWindowID(), LEFT_MOUSE_BUTTON_DOWN, event);
				mButtonPress = true;
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (mButtonPress) {
			mWindowMsgQueue.addMessage(getWindowID(), LEFT_MOUSE_BUTTON_UP, event);
			if (mMouseOver) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (getWindowID() != 0 || mParent != nullptr)
					{
						mWindowMsgQueue.addMessage(mWindowID, LEFT_MOUSE_BUTTON_CLICK, event);
					}
				}
			}
			mButtonPress = false;
		}
		break;
	case sf::Event::MouseMoved:
		if (mMouseOver)
		{
			if (!mMouseEnter)
			{
				mWindowMsgQueue.addMessage(getWindowID(), MOUSE_ENTER, event);
				mMouseEnter = true;
				mMouseLeave = false;
			}
			if (mButtonPress)
			{
				mWindowMsgQueue.addMessage(getWindowID(), LEFT_MOUSE_BUTTON_DOWN, event);
			}
			mWindowMsgQueue.addMessage(getWindowID(), MOUSE_MOVE, event);
		}
		else
		{
			if (!mMouseLeave)
			{
				mWindowMsgQueue.addMessage(getWindowID(), MOUSE_LEAVE, event);
				mMouseLeave = true;
				mMouseEnter = false;
			}
			if (mButtonPress)
			{
				mWindowMsgQueue.addMessage(getWindowID(), LEFT_MOUSE_BUTTON_DOWN, event);
			}
		}
		break;
	default:
		break;
	}

	for (int i = mChildren.size() - 1; i >= 0; i--)
	{
		mChildren.at(i)->events(event, window);
	}

	if (mEventHandlerClass != nullptr)
	{
		return mEventHandlerClass->messageCallBack(this, mWindowMsgQueue);
	}
	else
	{
		return 0;
	}
}