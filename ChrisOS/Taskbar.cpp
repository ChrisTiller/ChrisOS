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

	for (auto it = mChildren.cbegin(); it != mChildren.cend(); ++it)
	{
		it->second->draw(target, states);
	}
}