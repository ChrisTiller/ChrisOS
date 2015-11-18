#include "../include/system.h"

int main(int argc, char *argv[])
{

	System::getInstance()->init();
	System::getInstance()->systemLoop();
	System::getInstance()->close();

}
