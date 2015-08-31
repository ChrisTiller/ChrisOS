#pragma once
#include <SFML\Graphics.hpp>
#include <queue>

typedef unsigned int uint;

enum MESSAGES
{
	NO_MESSAGE,
	LEFT_MOUSE_BUTTON_DOWN,
	LEFT_MOUSE_BUTTON_UP,
	RIGHT_MOUSE_BUTTON_DOWN,
	RIGHT_MOUSE_BUTTON_UP,
	LEFT_MOUSE_BUTTON_CLICK,
	RIGHT_MOUSE_BUTTON_CLICK,
	MOUSE_MOVE,
	MOUSE_ENTER,
	MOUSE_LEAVE,
	MOUSE_DRAG,
	KEY_DOWN,
	KEY_UP,
	OKAY_BUTTON,
	CANCEL_BUTTON
};

struct controlMessage
{
	uint controlID;
	uint messageID;
	sf::Event event;
};

class MessageQueue
{
public:
	MessageQueue();
	~MessageQueue();

	void addMessage(uint controlID, uint message, sf::Event &event);
	controlMessage getMessage();
	bool hasMessage();
	void removeMessage();

private:
	std::queue<controlMessage> mMessageQueue;
};
