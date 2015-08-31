#pragma once

#include "Image.h"
#include "Label.h"

enum DesktopWindowID
{
	BUTTON = 1,
	LABEL,
	TASKBAR
};

class Desktop : public Window
{
public:
	static Desktop* getInstance();
	~Desktop()
	{
		instanceFlag = false;
	}

	void setBackground(const std::string imageName, const float sizeX, const float sizeY);

protected:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	Desktop()
	{}
	static bool instanceFlag;
	static Desktop *mDesktop;

	Image mBackground;

};

