#include "Desktop.h"


bool Desktop::instanceFlag = false;
Desktop* Desktop::mDesktop = nullptr;


Desktop* Desktop::getInstance()
{
	if (!instanceFlag)
	{
		mDesktop = new Desktop();
		instanceFlag = true;
	}
	return mDesktop;
}

void Desktop::setBackground(const std::string imageName, const float sizeX, const float sizeY)
{
	mBackground.setImage(imageName, sizeX, sizeY);
}

void Desktop::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(mBody, states);
	
	mBackground.draw(target, states);

	for (int i = 0; i < mChildren.size(); i++)
	{
		mChildren.at(i)->drawMe(target, states);
	}
}