#pragma once

#include "Button.h"
#include "TaskbarEventHandler.h"

enum TASKBAR_WINDOWS
{
	POWER_BUTTON = 1,
	DATE_TIME
};

class Taskbar : public Window
{
public:
	Taskbar();
	~Taskbar();

protected:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	Button mPowerButton;

	TaskbarEventHandler mEventHandler;
};

