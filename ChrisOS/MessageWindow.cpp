#include "MessageWindow.h"


MessageWindow::MessageWindow()
{
}


MessageWindow::~MessageWindow()
{
}

uint MessageWindow::show(int posX, int posY, int sizeX, int sizeY, std::string title)
{
	mMsgBox.setWindowPosition(posX, posY);
	mMsgBox.setSize(sf::Vector2f(sizeX, sizeY));


	mTitleBar.setWindowPosition(0, 0);
	mTitleBar.setSize(sf::Vector2f(sizeX, 32));
	mTitleBar.setFont("Oswald-Light.ttf");
	mTitleBar.setText(title);
	mTitleBar.setFontSize(20.0f);
	mTitleBar.setAlignment(MIDDLE_LEFT_ALIGNMENT);

	mTitleBar.setWindowID(1);

	mMsgBox.attachWindow(mTitleBar);

	uint returnValue = 0;

	Desktop *dp = dp->getInstance();

	while (returnValue == 0)
	{

		sf::Event event;
		while (System::getWindow().pollEvent(event))
		{
			mMsgBox.events(event, System::getWindow());
		}

		System::getWindow().clear();
		System::getWindow().draw(mMsgBox);
		System::getWindow().display();
	}

	return 0;
}
