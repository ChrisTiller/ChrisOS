#include "MessageWindow.h"
#include "MessageWindowHandler.h"

MessageWindow::MessageWindow(int posX, int posY, int sizeX, int sizeY, std::string title, std::string prompt)
{
	setWindowPosition(posX, posY);
	setSize(sizeX, sizeY);

	mTitleBar.setWindowPosition(0, 0);
	mTitleBar.setSize(sf::Vector2f(sizeX, 32));
	mTitleBar.setFont("Oswald-Light.ttf");
	mTitleBar.setFontSize(20.0f);
	mTitleBar.setText(title);
	mTitleBar.setAlignment(MIDDLE_LEFT_ALIGNMENT);
	mTitleBar.setBackgroundColor(0, 0, 0, 255);
	mTitleBar.setWindowID(3);

	attachWindow(mTitleBar);

	mButtonOK.setWindowPosition(0, sizeY - 30.0f);
	mButtonOK.setSize(50.0f, 26.0f);
	mButtonOK.setFont("Oswald-Light.ttf", 25.0f);
	mButtonOK.setText("OK");
	mButtonOK.setWindowID(BUTTON_OK);

	mButtonCancel = mButtonOK;

	mButtonCancel.setWindowPosition(60.0f, sizeY - 30.0f);
	mButtonCancel.setSize(50.0f, 26.0f);
	mButtonCancel.setFont("Oswald-Light.ttf", 25.0f);
	mButtonCancel.setText("Cancel");
	mButtonCancel.setWindowID(BUTTON_CANCEL);

	attachWindow(mButtonOK);
	attachWindow(mButtonCancel);

	mIsOpen = true;
}

MessageWindow::MessageWindow()
{

}

MessageWindow::~MessageWindow()
{
}

uint MessageWindow::show(Desktop * dp, int posX, int posY, int sizeX, int sizeY, std::string title, std::string prompt)
{
	
	return 0;
}

bool MessageWindow::isOpen()
{
	return mIsOpen;
}

void MessageWindow::close()
{
	mIsOpen = false;
}