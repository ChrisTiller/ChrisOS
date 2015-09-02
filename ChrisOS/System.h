#pragma once
#include <ctime>
#include "EventHandler.h"
#include "Button.h"
#include "Desktop.h"
#include "DesktopEventHandler.h"

//extern void controlCallBack(Control &control, MessageQueue &messageQueue);

class System
{
public:
	System();
	~System();

	void static init(int, int, bool);
	static void init();
	static sf::RenderWindow& getWindow();
	static sf::Vector2i getInternalResolution();
	static sf::Vector2f getPosition(float x, float y);
	static std::string getDateTime(const std::string &dateFormat, const std::string &timeFormat);
	static std::string getVersion();

	void static doEvents();

	void static systemLoop();

	static void draw();
private:
	void performTesting();

	static Label dateTime;

	static int mResolutionX;
	static int mResolutionY;
	static sf::Vector2i mInternalResolution;
	static sf::RenderWindow mWindow;
	//static Control sprite;
	//static Control myControl;
	//static Control control2;
	//static Control powerButton;
	//static Control taskBar;
	//static Control versionDisplay;
	static struct tm now;
	static time_t tNow;
};

