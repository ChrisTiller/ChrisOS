#include "System.h"
#include "Taskbar.h"


#define SYSTEM_QUIT 1000


int System::mResolutionX = 0;
int System::mResolutionY = 0;
sf::Vector2i System::mInternalResolution = { 1920, 1080 };
sf::RenderWindow System::mWindow;
struct tm System::now;
time_t System::tNow;
Label System::dateTime;
//Control System::sprite;
//Control System::taskBar;
//Control System::versionDisplay;
//Control System::myControl;
//Control System::control2;
//Control System::powerButton;

System::System()
{
}


System::~System()
{
}

void System::init(int resX, int resY, bool fullscreen)
{
	System::mResolutionX = resX;
	System::mResolutionY = resY;

	if (fullscreen)
	{
		System::mWindow.create(sf::VideoMode(mResolutionX, mResolutionY, 32), "Hello", sf::Style::Fullscreen);
	}
	else
	{
		System::mWindow.create(sf::VideoMode(mResolutionX, mResolutionY, 32), "Hello");
	}

	int newHeight = (1920 * resY) / resX;
	int displace = (newHeight - 1080) / (2);

	//System::mWindow.setView(sf::View(sf::FloatRect(0, displace, 1920, newHeight)));
}

void System::init()
{
	mWindow.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "Hi", sf::Style::Fullscreen);
}

sf::RenderWindow& System::getWindow()
{
	return System::mWindow;
}

sf::Vector2i System::getInternalResolution()
{
	return mInternalResolution;
}

sf::Vector2f System::getPosition(float x, float y)
{
	return sf::Vector2f(x / mInternalResolution.x * mWindow.getSize().x, y / mInternalResolution.y * mWindow.getSize().y);
}

std::string System::getDateTime(const std::string &dateFormat, const std::string &timeFormat)
{
	time_t tNow = time(0);
	localtime_s(&now, &tNow);

	std::string stringDate = "";
	std::string stringTime = "";
	bool isMorning = true;

	if (dateFormat == "mm/dd/yy")
	{
		if ((now.tm_mon + 1) < 10)
		{
			stringDate += "0";
		}

		stringDate += std::to_string(now.tm_mon + 1) +  "/";

		if (now.tm_mday < 10)
		{
			stringDate += "0";
		}

		stringDate += std::to_string(now.tm_mday) + "/";

		stringDate += std::to_string((now.tm_year + 1900) % 100);
	} 
	else if (dateFormat == "mm/dd/yyyy")
	{
		if ((now.tm_mon + 1) < 10)
		{
			stringDate += "0";
		}

		stringDate += std::to_string(now.tm_mon + 1) + "/";

		if (now.tm_mday < 10)
		{
			stringDate += "0";
		}

		stringDate += std::to_string(now.tm_mday) + "/";

		stringDate += std::to_string(now.tm_year + 1900);
	}
	else if (dateFormat == "m/d/yyyy")
	{
		stringDate = (std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_mday) + "/" + std::to_string(now.tm_year + 1900));
	}
	else if (dateFormat == "m/d/yy")
	{
		stringDate = (std::to_string(now.tm_mon + 1) + "/" + std::to_string(now.tm_mday) + "/" + std::to_string((now.tm_year + 1900) % 100));
	}

	if (timeFormat == "hh:mm:ss")
	{
		if (now.tm_hour < 10)
		{
			stringTime += "0" + std::to_string(now.tm_hour);
		}
		else if (now.tm_hour > 12)
		{
			stringTime += "0" + std::to_string(now.tm_hour - 12);
			isMorning = false;
		}
		else
		{
			stringTime += std::to_string(now.tm_hour);
		}

		stringTime += ":";

		if (now.tm_min < 10)
		{
			stringTime += "0";
		}

		stringTime += std::to_string(now.tm_min) + ":";

		if (now.tm_sec < 10)
		{
			stringTime += "0";
		}

		stringTime += std::to_string(now.tm_sec);
	}
	else if (timeFormat == "h:m:s")
	{
		if (now.tm_hour > 12)
		{
			stringTime += std::to_string(now.tm_hour - 12);
			isMorning = false;
		}
		else
		{
			stringTime += std::to_string(now.tm_hour);
		}

		stringTime += ":";

		stringTime += std::to_string(now.tm_min);

		stringTime += ":";

		stringTime += std::to_string(now.tm_sec);
	}
	else if (timeFormat == "h:m")
	{
		if (now.tm_hour > 12)
		{
			stringTime += std::to_string(now.tm_hour - 12);
			isMorning = false;
		}
		else
		{
			stringTime += std::to_string(now.tm_hour);
		}

		stringTime += ":";

		stringTime += std::to_string(now.tm_min);
	}
	else if (timeFormat == "hh:mm")
	{
		if (now.tm_hour < 10)
		{
			stringTime += "0" + std::to_string(now.tm_hour);
		}
		else if (now.tm_hour > 12)
		{
			stringTime += "0" + std::to_string(now.tm_hour - 12);
			isMorning = false;
		}
		else
		{
			stringTime += std::to_string(now.tm_hour);
		}

		stringTime += ":";

		if (now.tm_min < 10)
		{
			stringTime += "0";
		}

		stringTime += std::to_string(now.tm_min);
	}

	if (isMorning)
	{
		return stringDate + "  " + stringTime + " AM";
	}
	else
	{
		return stringDate + "  " + stringTime + " PM";
	}
}

std::string System::getVersion()
{
	return "0.1.0.0";
}

void System::systemLoop()
{

	Desktop *dp = nullptr;

	dp = dp->getInstance();

	//dp->setBackground("background-hd-wallpapers.jpg", 1920, 1080);
	dp->setWindowPosition(0, 0);
	dp->setSize(1920, 1080);
	dp->setBackgroundColor(0, 0, 180, 200);

	DesktopEventHandler dpHandle;

	dp->setEventHandlerClass(&dpHandle);

	Taskbar tskbar;

	TaskbarEventHandler eventHandler;
	tskbar.setPosition(0, 0);
	tskbar.setSize(1920, 33);
	tskbar.setBackgroundColor(255, 255, 255);
	tskbar.setEventHandlerClass(&eventHandler);

	Button mPowerButton;
	mPowerButton.setSize(25.0f, 25.0f);
	mPowerButton.setImage("power-off.png", 16, 16);
	mPowerButton.setWindowID(POWER_BUTTON);
	mPowerButton.setImageAlignment(MIDDLE_MIDDLE_ALIGNMENT);

	//dateTime(System::getDateTime("mm/dd/yy", "hh:mm"));
	dateTime.setSize(50.0f, 29.0f);
	dateTime.setFontSize(28.0f);

	dateTime.setWindowID(DATE_TIME);
	tskbar.attachWindow(dateTime);
	dateTime.setWindowPosition((tskbar.getSize().x / 2) - (dateTime.getTextLength() / 2), 2);

	tskbar.attachWindow(mPowerButton);
	mPowerButton.setWindowPosition(1890.0f, 4.5f);

	tskbar.setWindowID(1);

	dp->attachWindow(tskbar);

	Label versionLabel("Version: " + System::getVersion());
	versionLabel.setSize(35, 21);
	versionLabel.setFontSize(20.0f);
	versionLabel.setTextColor(255, 255, 255, 255);
	versionLabel.setBackgroundColor(255, 255, 255, 0);
	versionLabel.setWindowID(2);
	dp->attachWindow(versionLabel);

	versionLabel.setWindowPosition(1790, 1050);

	while (mWindow.isOpen())
	{
		doEvents();
	}
}

void System::doEvents()
{

	Desktop *dp = dp->getInstance();

	dateTime.setText(System::getDateTime("mm/dd/yy", "hh:mm"));
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				mWindow.close();
				break;
			default:
				break;
			}
		}
		dp->events(event, mWindow);
	}

	draw();
}

void System::draw()
{
	//mWindow.draw(sprite);
	//mWindow.draw(taskBar);
	//mWindow.draw(versionDisplay);
	Desktop *dp = dp->getInstance();
	mWindow.clear();
	mWindow.draw(*dp);
	mWindow.display();
}



//void controlCallBack(Control &control, MessageQueue &messageQueue)
//{	
//	static int xOffset;
//	static int yOffset;
//	static bool dragStarted;
//
//	//MessageWindow mBox;
//	while (messageQueue.hasMessage())
//	{
//		switch (messageQueue.getMessage().messageID)
//		{
//		case LEFT_MOUSE_BUTTON_DOWN:
//			switch (messageQueue.getMessage().controlID)
//			{
//			case 1:
//				if (!dragStarted)
//				{
//					dragStarted = true;
//				}
//				else
//				{
//					control.setPosition(sf::Mouse::getPosition(System::getWindow()).x - xOffset, sf::Mouse::getPosition(System::getWindow()).y- yOffset);
//				}
//
//				xOffset = sf::Mouse::getPosition(System::getWindow()).x - control.getPosition().x;
//				yOffset = sf::Mouse::getPosition(System::getWindow()).y - control.getPosition().y;
//				break;
//			case 3:
//				control.setBackgroundColor(sf::Color(0, 0, 155, 120));
//				break;
//			default:
//				break;
//			}
//			break;
//		case LEFT_MOUSE_BUTTON_UP:
//			switch (messageQueue.getMessage().controlID)
//			{
//			case 1:
//				dragStarted = false;
//				break;
//			case 3:
//				control.setBackgroundColor(sf::Color(0, 0, 155, 0));
//				break;
//			default:
//				break;
//			}
//			break;
//		case LEFT_MOUSE_BUTTON_CLICK:
//			switch (messageQueue.getMessage().controlID)
//			{
//			case 1:
//				
//				control.setString("Please?!");
//				break;
//			case 2:
//				control.setString("I will cry");
//				break;
//			case 3:
//				//mBox.show(500, 500, 250, 200, "Exit?");
//				System::getWindow().close();
//			default:
//				break;
//			}
//			break;
//		case MOUSE_ENTER:
//			if (messageQueue.getMessage().controlID == 1)
//			{
//				control.setTextColor(sf::Color(0, 255, 0));
//				control.setBackgroundColor(sf::Color(51, 153, 255, 35));
//				control.setOutlineColor(sf::Color(51, 153, 255, 100));
//			}
//			if (messageQueue.getMessage().controlID == 2)
//			{
//				control.setTextColor(sf::Color(255, 0, 255));
//			}
//			if (messageQueue.getMessage().controlID == 3)
//			{
//				control.setOutlineColor(sf::Color(0, 0, 0));
//				control.setOutlineThickness(1.0f);
//			}
//			break;
//		case MOUSE_LEAVE:
//			switch (messageQueue.getMessage().controlID)
//			{
//			case 1:
//				control.setTextColor(sf::Color(0, 0, 0));
//				control.setBackgroundColor(sf::Color(120, 80, 180, 0));
//				control.setOutlineColor(sf::Color(120, 80, 130, 0));
//				break;
//			case 2:
//				control.setTextColor(sf::Color(0, 0, 0));
//				break;
//			case 3:
//				control.setOutlineThickness(0.0f);
//				control.setBackgroundColor(sf::Color(0, 0, 155, 0));
//				break;
//			default:
//				break;
//			}
//		case MOUSE_MOVE:
//			switch (messageQueue.getMessage().controlID)
//			{
//			case 1:
//
//				break;
//			default:
//				break;
//			}
//			break;
//		default:
//			break;
//		}
//		messageQueue.removeMessage();
//	}
//}