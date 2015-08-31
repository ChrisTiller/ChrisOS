#include <ctime>
#include <SFML/Graphics.hpp>
#include "Control.h"
#include "System.h"
#include "MessageWindow.h"

//void controlCallBack(Control &control, uint controlID, uint messageType, const sf::Event &event);
void controlCallBack(Control &control, MessageQueue &messageQueue);

int main()
{

	//System::init(1920, 1080, true);
	System::init(800, 600, false);

	System::systemLoop();

	return 0;
}

