#pragma once

#include <map>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "EventHandler.h"
#include "ResourceManager.h"

#include "SharedWindowPtr.h"
#include "SharedWindowPtr.inl"

enum ALIGNMENT
{
	TOP_LEFT_ALIGNMENT,
	TOP_MIDDLE_ALIGNMENT,
	TOP_RIGHT_ALIGNMENT,
	MIDDLE_LEFT_ALIGNMENT,
	MIDDLE_MIDDLE_ALIGNMENT,
	MIDDLE_RIGHT_ALIGNMENT,
	BOTTOM_LEFT_ALIGNMENT,
	BOTTOM_MIDDLE_ALIGNMENT,
	BOTTOM_RIGHT_ALIGNMENT
};

enum class WindowType
{
	DESKTOP,
	TASKBAR,
	WINDOW,
	BUTTON,
	LABEL,
	IMAGE
};

class Window : public sf::Drawable, public sf::Transformable
{
public:

	/*struct Ptr
	{
		typedef SharedWindowPtr<Window> PTR;
	};*/
	//using Ptr = SharedWindowPtr<Window>;
	typedef SharedWindowPtr<Window> Ptr;
	//SharedWindowPtr<Window> Ptr;

	Window();
	/*Window(const sf::Vector2f size);
	Window(const float x, const float y);
	Window(const sf::Uint32 windowID, const sf::Vector2f size, EventHandler *eventHandlerClass);*/
	virtual ~Window();

	sf::Vector2f& getSize();

	Window* getParent();

	sf::Vector2f getPosition();

	EventHandler *getEventHandler();

	void addChildWindow(const ::Window::Ptr &windowPtr, const std::string &windowName = "");

	void sendMessage(uint controlID, uint message, sf::Event &event);

	void setBackgroundColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha = 255);

	void setOutlineColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha = 255);

	void setOutlineThickness(const float thickness);

	void setPosition(const float x, const float y);

	void setPosition(const sf::Vector2f &pos);

	void setSize(const float x, const float y);

	void setSize(const sf::Vector2f &size);

	virtual bool mouseOnWindow(float x, float y);

	virtual void mouseEnteredWindow();

	virtual void mouseLeftWindow();

	virtual void leftMousePressed(float x, float y);

	virtual void leftMouseReleased(float x, float y);

	virtual void mouseMoved(float x, float y);

	virtual void windowFocus();

	virtual void windowUnfocused();

	virtual void mouseNotOnWindow();

	virtual void mouseNoLongerDown();

	int eventHandle(sf::Event &event);

protected:

	// contains the size of the window
	sf::Vector2f mSize;
	sf::RectangleShape mBody;

	// vector of window pointers that point to child windows if any
	std::map<std::string, Ptr> mChildren;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:

	::Window::Ptr mouseOnWhichWindow(float x, float y);

	void initialize(Window *parent);

	void setEventHandler(EventHandler *eventHandler);

	bool mMouseOver;
	bool mMouseEnter;
	bool mMouseLeave;
	bool mMouseDown;

	bool mFocused;

	bool mDraggable;
	bool mContainer;

	// colors for the window to use
	sf::Color mBackgroundColor;
	sf::Color mOutlineColor;

	// message queue for the window
	MessageQueue mWindowMsgQueue;

	// pointer pointing to a parent window if any
	Window *mParent;

	// active window within the window
	Window* mFocusedWindow;

	// event callback used to send events to
	EventHandler *mEventHandler;

	// type of window we're dealing with
	WindowType mType;

	friend class Taskbar;
	friend class Desktop;
};
