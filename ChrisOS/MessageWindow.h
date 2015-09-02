#pragma once
#include "System.h"

enum MESSAGE_RETURN {
	BUTTON_OK = 8,
	BUTTON_CANCEL,
	BUTTON_EXIT
};

//extern void messageCallBack(Control &control, MessageQueue &messageQueue);

class MessageWindow : public Window
{
public:
	MessageWindow();
	MessageWindow(int posX, int posY, int sizeX, int sizeY, std::string title, std::string prompt);
	~MessageWindow();

	uint show(Desktop *dp, int posX, int posY, int sizeX, int sizeY, std::string title, std::string prompt);

	bool isOpen();

	void close();
private:

	Window mMsgBox;

	Button mButtonOK;
	Button mButtonCancel;

	Label mTitleBar;
	Label mPrompt;

	bool mIsOpen;
};

