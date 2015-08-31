#include "Button.h"


Button::Button(const std::string text, const std::string fontName, const float fontSize)
{
	setText(text);
	setFont(fontName, fontSize);
}

Button::~Button()
{
}

void Button::setFont(const std::string fontName, const float fontSize)
{
	mLabel.setFont(fontName);
	mLabel.setFontSize(fontSize);
}

void Button::setImage(const std::string imageName, const float sizeX, const float sizeY)
{
	mImage.setImage(imageName, sizeX, sizeY);
	attachWindow(mImage);
}

void Button::setImageAlignment(sf::Uint32 alignment)
{
	mImage.setImageAlignment(alignment);
	update();
}

void Button::setText(const std::string text)
{
	mLabel.setText(text);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBody, states);

	mImage.draw(target, states);
	mLabel.draw(target, states);

	/*for (int i = 0; i < mChildren.size(); i++)
	{
		mChildren.at(i)->drawMe(target, states);
	}*/
}

void Button::update()
{
	//mImage.setOrigin(0, 0);

	switch (mImage.getAlignment())
	{
	case TOP_LEFT_ALIGNMENT:
		mImage.setPosition(0, 0);
		break;
	case TOP_MIDDLE_ALIGNMENT:
		mImage.setPosition(((float)mImage.getImageSize().x / 2), 0);
		break;
	case TOP_RIGHT_ALIGNMENT:
		mImage.setPosition(mSize.x - (float)mImage.getImageSize().x - 5.0f, 0);
		break;
	case MIDDLE_LEFT_ALIGNMENT:
		mImage.setPosition(0, (mSize.y / 2) - ((float)mImage.getImageSize().y / 2));
		break;
	case MIDDLE_MIDDLE_ALIGNMENT:
		mImage.setPosition((getSize().x / 2) - ((float)mImage.getImageSize().x / 2), (getSize().y / 2) - ((float)mImage.getImageSize().y / 2));
		break;
	case MIDDLE_RIGHT_ALIGNMENT:
		mImage.setPosition(mSize.x - ((float)mImage.getImageSize().x) - 5.0f, (mSize.y / 2) - ((float)mImage.getImageSize().y / 2));
		break;
	case BOTTOM_LEFT_ALIGNMENT:
		mImage.setPosition(0, mSize.y - (float)mImage.getImageSize().y);
		break;
	case BOTTOM_MIDDLE_ALIGNMENT:
		mImage.setPosition((mSize.x / 2) - ((float)mImage.getImageSize().x / 2), mSize.y - (float)mImage.getImageSize().y);
		break;
	case BOTTOM_RIGHT_ALIGNMENT:
		mImage.setPosition(mSize.x - (float)mImage.getImageSize().x - 5.0f, mSize.y - (float)mImage.getImageSize().y);
		break;
	default:
		break;
	}
}