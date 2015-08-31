#include "MessageQueue.h"


MessageQueue::MessageQueue()
{
}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::addMessage(uint controlID, uint message, sf::Event &event)
{
	controlMessage mess;
	mess.controlID = controlID;
	mess.messageID = message;
	mess.event = event;
	mMessageQueue.push(mess);
}

controlMessage MessageQueue::getMessage()
{
	return mMessageQueue.front();
}

void MessageQueue::removeMessage()
{
	if (mMessageQueue.size() > 0)
	{
		mMessageQueue.pop();
	}
}

bool MessageQueue::hasMessage()
{
	if (mMessageQueue.size() > 0)
	{
		return true;
	}
	return false;
}
