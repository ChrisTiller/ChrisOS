#include "MessageWindow.h"
#include "MessageWindowHandler.h"

MessageWindow::MessageWindow(int posX, int posY, int sizeX, int sizeY, std::string title, std::string prompt)
{
	this->setWindowPosition(posX, posY);
	this->setSize(sizeX, sizeY);

	mTitleBar.setWindowPosition(0, 0);
	mTitleBar.setSize(sf::Vector2f(sizeX, 32));
	mTitleBar.setFont("Oswald-Light.ttf");
	mTitleBar.setFontSize(20.0f);
	mTitleBar.setText(title);
	mTitleBar.setAlignment(MIDDLE_LEFT_ALIGNMENT);
	mTitleBar.setWindowID(3);

	this->attachWindow(mTitleBar);

	mButtonOK.setText("OK");
	mButtonOK.setFont("Oswald-Light.ttf", 25.0f);
	mButtonOK.setWindowID(BUTTON_OK);
	mButtonOK.setSize(50.0f, 26.0f);
	mButtonOK.setWindowPosition(0, sizeY - 30.0f);

	mButtonCancel = mButtonOK;

	mButtonCancel.setText("Cancel");
	mButtonCancel.setFont("Oswald-Light.ttf", 25.0f);
	mButtonCancel.setWindowID(BUTTON_CANCEL);
	mButtonCancel.setWindowPosition(60.0f, sizeY - 30.0f);

	this->attachWindow(mButtonOK);
	this->attachWindow(mButtonCancel);

}


MessageWindow::~MessageWindow()
{
}

uint MessageWindow::show(int posX, int posY, int sizeX, int sizeY, std::string title, std::string prompt)
{
	return 0;
}
