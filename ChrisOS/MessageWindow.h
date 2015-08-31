#pragma once
#include "System.h"

enum {
	BUTTON_OK = 1,
	BUTTON_CANCEL,
	BUTTON_EXIT
};

//extern void messageCallBack(Control &control, MessageQueue &messageQueue);

class MessageWindow
{
public:
	MessageWindow();
	~MessageWindow();

	uint show(int posX, int posY, int sizeX, int sizeY, std::string title);

private:

	Window mMsgBox;

	Button mButtonOK;
	Button mButtonCancel;

	Label mTitleBar;
	Label mPrompt;
};

