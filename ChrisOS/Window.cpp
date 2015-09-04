#include "Window.h"

Window::Window() :
mContainer(nullptr),
mFocusedWindow(nullptr),
mMouseOver(false),
mMouseEnter(false),
mMouseLeave(false),
mMouseDown(false),
mFocused(false),
mDraggable(false),
mType(WindowType::WINDOW)
{
}

Window::~Window()
{
}

sf::Vector2f& Window::getSize()
{
	return mSize;
}

Window* Window::getParent()
{
	return mParent;
}

sf::Vector2f Window::getPosition()
{
	return sf::Vector2f(mBody.getLocalBounds().left, mBody.getLocalBounds().height);
}

EventHandler *Window::getEventHandler()
{
	return mEventHandler;
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

void Window::setOutlineColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha)
{
	mOutlineColor = sf::Color(red, green, blue, alpha);
	mBody.setOutlineColor(sf::Color(red, green, blue, alpha));
}

void Window::setOutlineThickness(float thickness)
{
	mBody.setOutlineThickness(thickness);
}

void Window::setSize(const sf::Vector2f &size)
{
	mSize = size;
	mBody = sf::RectangleShape(size);
}
//
//void Window::setSize(const float x, const float y)
//{
//	sf::Vector2f newSize = sf::Vector2f(x / System::getInternalResolution().x * System::getWindow().getSize().x, y / System::getInternalResolution().y * System::getWindow().getSize().y);
//	mSize = newSize;
//	mBody = sf::RectangleShape(newSize);
//}

void Window::setPosition(const float x, const float y)
{
	//sf::Vector2f newSize = sf::Vector2f(x / System::getInternalResolution().x * System::getWindow().getSize().x, y / System::getInternalResolution().y * System::getWindow().getSize().y);
	sf::Vector2f newSize = sf::Vector2f(x, y);
	setPosition(newSize.x, newSize.y);
}

void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBody, states);

	for (auto it = mChildren.cbegin(); it != mChildren.cend(); ++it)
	{
		it->second->draw(target, states);
	}
}

int Window::eventHandle(sf::Event &event)
{
	Window::Ptr window;
	switch (event.type)
	{

	case sf::Event::MouseMoved:

		for (auto it = mChildren.cbegin(); it != mChildren.cend(); ++it)
		{
			if ((it->second->mMouseDown) && ((it->second->mDraggable) || (it->second->mContainer)))
			{
				it->second->mouseMoved(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
				return true;
			}
		}

		window = mouseOnWhichWindow(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
		if (window != nullptr)
		{
			while (window->mType == WindowType::WINDOW && window != nullptr)
			{
				window = window->mouseOnWhichWindow(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			}
			if (window != nullptr)
			{
				window->mouseMoved(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
				return true;
			}
		}
		break;

	case sf::Event::MouseButtonPressed:

		switch (event.mouseButton.button)
		{

		case sf::Mouse::Left:

			window = mouseOnWhichWindow(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			if (window != nullptr)
			{
				//focusWindow(window.getWindow());

				while (window->mType == WindowType::WINDOW && window != nullptr)
				{
					window = window->mouseOnWhichWindow(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
				}
				if (window != nullptr)
				{
					window->leftMousePressed(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
					return true;
				}
			}
			else
			{
				//unfocusWindows();
			}

			break;

		default:
			return false;
		}
		break;

	case sf::Event::MouseButtonReleased:

		switch (event.mouseButton.button)
		{

		case sf::Mouse::Left:

			window = mouseOnWhichWindow(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			if (window != nullptr)
			{
				while (window->mType == WindowType::WINDOW)
				{
					window = window->mouseOnWhichWindow(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
				}
				if (window != nullptr)
				{
					window->leftMousePressed(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
					return true;
				}
			}

			for (auto it = mChildren.cbegin(); it != mChildren.cend(); ++it)
			{
				if (it->second != window)
				{
					it->second->mouseNoLongerDown();
				}
			}

			if (window != nullptr)
			{
				return true;
			}
			else
			{
				return false;
			}

			break;
		default:
			return false;
		}
		break;

	default:
		return false;
	}

	return false;
}

void Window::initialize(Window *parent)
{
	mParent = parent;
	setEventHandler(mParent->getEventHandler());
}

void Window::setEventHandler(EventHandler *eventHandler)
{
	mEventHandler = eventHandler;

	for (auto it = mChildren.cbegin(); it != mChildren.cend(); ++it)
	{
		it->second->setEventHandler(eventHandler);
	}
}

void Window::addChildWindow(const Window::Ptr &windowPtr, const std::string &windowName)
{
	assert(windowPtr != nullptr);

	if (auto it = mChildren.find(windowName) != mChildren.end()) return;

	windowPtr->initialize(this);
	mChildren.insert(std::make_pair(windowName, windowPtr));
}

void Window::mouseMoved(float x, float y)
{
	if (!mMouseOver)
	{
		mouseEnteredWindow();
	}

	mMouseOver = true;
}

bool Window::mouseOnWindow(float x, float y)
{
	if (getTransform().transformRect(sf::FloatRect(0, 0, getSize().x, getSize().y)).contains(x, y))
	{
		return true;
	}

	if (mMouseOver)
	{
		mouseLeftWindow();

		mMouseOver = false;
	}
	return false;
}

void Window::mouseEnteredWindow()
{
	mEventHandler->messageCallBack(mParent, this, MOUSE_ENTER);
}

void Window::mouseLeftWindow()
{
	mEventHandler->messageCallBack(mParent, this, MOUSE_LEAVE);
}

void Window::leftMousePressed(float x, float y)
{
	mMouseDown = true;

	mEventHandler->messageCallBack(mParent, this, LEFT_MOUSE_BUTTON_DOWN);
}

void Window::leftMouseReleased(float x, float y)
{
	mEventHandler->messageCallBack(mParent, this, LEFT_MOUSE_BUTTON_UP);

	if (mMouseDown)
	{
		mEventHandler->messageCallBack(mParent, this, LEFT_MOUSE_BUTTON_CLICK);

		mMouseDown = false;
	}
}

void Window::windowFocus()
{

}

void Window::windowUnfocused()
{

}

void Window::mouseNotOnWindow()
{
	if (mMouseOver)
	{
		mouseLeftWindow();
	}

	mMouseOver = false;
}

void Window::mouseNoLongerDown()
{
	for (auto it = mChildren.cbegin(); it != mChildren.cend(); ++it)
	{	
		if (it->second->mType == WindowType::WINDOW)
		{
			it->second->mouseNoLongerDown();
		}
		else
		{
			mMouseDown = false;
		}
	}
	mMouseDown = false;
}

Window::Ptr Window::mouseOnWhichWindow(float x, float y)
{
	bool found = false;
	Window::Ptr window;

	for (auto it = mChildren.crend(); it != mChildren.crbegin(); ++it)
	{
		if (!found)
		{
			if (it->second->mouseOnWindow(x, y))
			{
				window = it->second;
				found = true;
			}
		}
		else
		{
			it->second->mouseNotOnWindow();
		}
	}

	return window;
}