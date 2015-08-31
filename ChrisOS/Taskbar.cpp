#include "Taskbar.h"


Taskbar::Taskbar()
{
}


Taskbar::~Taskbar()
{
}


void Taskbar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(mBody, states);

	//mBackground.draw(target, states);

	for (int i = 0; i < mChildren.size(); i++)
	{
		mChildren.at(i)->drawMe(target, states);
	}
}