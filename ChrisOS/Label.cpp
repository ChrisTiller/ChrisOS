#include "Label.h"
#include "System.h"

Label::Label(const std::string text, const std::string font, const float fontSize, sf::Uint32 alignment) :
mAlignment(alignment)
{
	setFont(font);
	setText(text);
	setFontSize(fontSize);
	mText.setColor(sf::Color(0, 0, 0, 255));
	setBackgroundColor(255, 255, 255, 0);
}

Label::~Label()
{
}

sf::Color Label::getTextColor()
{
	return mText.getColor();
}

sf::Uint32 Label::getAlignment()
{
	return mAlignment;
}

std::string Label::getFontName()
{
	return mFont.getInfo().family;
}

float Label::getFontSize()
{
	return mText.getCharacterSize();
}

void Label::setAlignment(sf::Uint32 alignmet)
{
	mAlignment = alignmet;
}

void Label::setFont(const std::string font)
{
	mFont = ResourceManager::getFont(font);
	mText.setFont(mFont);
}

void Label::setTextColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha)
{
	mText.setColor(sf::Color(red, green, blue, alpha));
}

void Label::setText(const std::string text)
{
	mText.setString(text);
}

void Label::setFontSize(float size)
{
	float newSize = size / System::getInternalResolution().y * System::getWindow().getSize().y;
	mText.setCharacterSize(newSize);
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBody, states);
	target.draw(mText, states);
}

void Label::update()
{
	mText.setOrigin(0, 0);

	switch (mAlignment)
	{
	case TOP_LEFT_ALIGNMENT:
		mText.setPosition(0, 0);
		break;
	case TOP_MIDDLE_ALIGNMENT:
		mText.setPosition((mSize.x / 2) - (mText.getLocalBounds().width / 2), 0);
		break;
	case TOP_RIGHT_ALIGNMENT:
		mText.setPosition(mSize.x - (mText.getLocalBounds().width) - 5.0f, 0);
		break;
	case MIDDLE_LEFT_ALIGNMENT:
		mText.setPosition(0, (mSize.y / 2) - (mText.getCharacterSize() / 2));
		break;
	case MIDDLE_MIDDLE_ALIGNMENT:
		mText.setPosition((mSize.x / 2) - (mText.getLocalBounds().width / 2), (mSize.y / 2) - (mText.getCharacterSize() / 2));
		break;
	case MIDDLE_RIGHT_ALIGNMENT:
		mText.setPosition(mSize.x - (mText.getLocalBounds().width) - 5.0f, (mSize.y / 2) - (mText.getCharacterSize() / 2));
		break;
	case BOTTOM_LEFT_ALIGNMENT:
		mText.setPosition(0, mSize.y - mText.getCharacterSize());
		break;
	case BOTTOM_MIDDLE_ALIGNMENT:
		mText.setPosition((mSize.x / 2) - (mText.getLocalBounds().width / 2), mSize.y - mText.getCharacterSize());
		break;
	case BOTTOM_RIGHT_ALIGNMENT:
		mText.setPosition(mSize.x - mText.getLocalBounds().width - 5.0f, mSize.y - mText.getCharacterSize());
		break;
	default:
		break;
	}
}