#pragma once

#include "Button.h"
#include "TaskbarEventHandler.h"

enum TASKBAR_WINDOWS
{
	POWER_BUTTON = 15,
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


	friend class Window;
};

