#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "EventHandler.h"
#include "ResourceManager.h"

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

class Window : public sf::Drawable, public sf::Transformable
{
public:
	Window();
	Window(const sf::Vector2f size);
	Window(const float x, const float y);
	Window(const sf::Uint32 windowID, const sf::Vector2f size, EventHandler *eventHandlerClass);
	~Window();

	sf::Vector2f& getSize();
	Window* getParent();
	sf::Uint32 getWindowID();
	sf::Vector2f getWindowPosition();
	sf::FloatRect getWindowRect();
	EventHandler *getEventHandler();

	void attachWindow(Window &window);
	void sendMessage(uint controlID, uint message, sf::Event &event);
	void setBackgroundColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha = 255);
	void setEventHandlerClass(EventHandler *eventHandlerClass);
	void setOutlineColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha = 255);
	void setOutlineThickness(const float thickness);
	void setParent(Window &window);
	void setWindowPosition(const float x, const float y);
	void setWindowPosition(const sf::Vector2f pos);
	void setSize(const float x, const float y);
	void setSize(const sf::Vector2f size);
	void setWindowID(const sf::Uint32 windowID);

	int events(sf::Event &event, sf::RenderWindow &window);
	void drawMe(sf::RenderTarget &target, sf::RenderStates states) const;

protected:

	// contains the size of the window
	sf::Vector2f mSize;
	sf::RectangleShape mBody;

	// vector of window pointers that point to child windows if any
	std::vector<Window*> mChildren;

private:

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	bool mMouseOver;
	bool mMouseEnter;
	bool mMouseLeave;
	bool mButtonPress;

	// keep track of the ID of the window
	sf::Uint32 mWindowID;
	int mNumWindows;

	// colors for the window to use
	sf::Color mBackgroundColor;
	sf::Color mOutlineColor;

	// message queue for the window
	MessageQueue mWindowMsgQueue;

	// pointer pointing to a parent window if any
	Window *mParent;

	// event callback used to send events to
	EventHandler *mEventHandlerClass;
};
