#include "Control.h"
#include "System.h"
#include <assert.h>

#ifdef ENABLE_TRACE
#  ifdef _MSC_VER
#    include <windows.h>
#    include <sstream>
#    define TRACE(x)                           \
     do {  std::stringstream s;  s << (x);     \
           OutputDebugString(s.str().c_str()); \
	         } while(0)
#  else
#    include <iostream>
#    define TRACE(x)  std::clog << (x)
#  endif        // or std::cerr << (x) << std::flush
#else
#  define TRACE(x)
#endif

Control::Control() : mMouseEnter(false), mMouseOver(false), mButtonPress(false), mControlID(0), mNumControls(0), mAlignment(MIDDLE_MIDDLE_ALIGNMENT)
{
	setTextColor(sf::Color(0, 0, 0));
	setTextSize(10.0f);
}

Control::Control(const sf::Vector2f size) : mMouseEnter(false), mMouseOver(false), mButtonPress(false), mControlID(0), mNumControls(0), mAlignment(MIDDLE_MIDDLE_ALIGNMENT)
{
	setSize(size);
	setTextColor(sf::Color(0, 0, 0));
	setTextSize(10.0f);
}

Control::~Control()
{
}

void Control::setCallBack(::function callback)
{
	mCallBack = callback;
}

void Control::setAlignment(uint alignment)
{
	mAlignment = alignment;
	update();
}

void Control::addChildControl(Control &control)
{
	if (control.getControlID() == 0)
	{
		return;
	}
	for (int i = 0; i < mChildren.size(); i++)
	{
		if (mChildren.at(i)->getControlID() == control.getControlID())
		{
			return;
		}
	}
	control.setParent(*this);
	mChildren.push_back(&control);
	mNumControls++;
}

uint Control::getControlID()
{
	return mControlID;
}

void Control::setControlID(uint controlID)
{
	mControlID = controlID;
}

void Control::setBackgroundColor(const sf::Color &backgroundColor)
{
	mBackgroundColor = backgroundColor;
	mBody.setFillColor(backgroundColor);
}

void Control::setTextColor(const sf::Color &textColor)
{
	mTextColor = textColor;
	mText.setColor(textColor);
}

void Control::setOutlineColor(const sf::Color &outlineColor)
{
	mBody.setOutlineColor(outlineColor);
}

void Control::setFont(sf::Font &font)
{
	mFont = font;
	mText.setFont(mFont);
	update();
}

void Control::setFont(const std::string font)
{
	mFont = ResourceManager::getFont(font);
	mText.setFont(mFont);
	update();
}

void Control::setSize(const sf::Vector2f size)
{
	sf::Vector2f newSize = sf::Vector2f(size.x / System::getInternalResolution().x * System::getWindow().getSize().x, size.y / System::getInternalResolution().y * System::getWindow().getSize().y);
	mSize = newSize;
	mBody.setSize(newSize);
	update();
}

void Control::setSprite(const std::string textureName)
{
	mSprite.setTexture(ResourceManager::getTexture(textureName));
}

void Control::setString(const std::string str)
{
	mText.setString(str);
	update();
}

void Control::setOutlineThickness(const float thickness)
{
	mBody.setOutlineThickness(thickness);
}

void Control::setParent(Control &control)
{
	mParent = &control;
}

void Control::setTextSize(float size)
{
	float newSize = size / System::getInternalResolution().y * System::getWindow().getSize().y;
	mTextSize = newSize;
	mText.setCharacterSize(newSize);
	update();
}

void Control::setControlPosition(float x, float y)
{
	sf::Vector2f newSize = sf::Vector2f(x / System::getInternalResolution().x * System::getWindow().getSize().x, y / System::getInternalResolution().y * System::getWindow().getSize().y);
	setPosition(newSize.x, newSize.y);
}


void Control::events(sf::Event &event, sf::RenderWindow &window, ::function callback)
{
	sf::FloatRect body(getPosition().x, getPosition().y, mSize.x, mSize.y);

	if ((getControlID() == 0) && mParent != nullptr)
	{
		return;
	}

	mMouseOver = false;
	if (body.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		mMouseOver = true;
	}

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (mMouseOver) {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				mControlMessageQueue.addMessage(getControlID(), LEFT_MOUSE_BUTTON_DOWN, event);
				mButtonPress = true;
			}
		}
			mControlMessageQueue.addMessage(getControlID(), MOUSE_DRAG, event);
		break;
	case sf::Event::MouseButtonReleased:
		if (mButtonPress) {
			mControlMessageQueue.addMessage(getControlID(), LEFT_MOUSE_BUTTON_UP, event);
			if (mMouseOver) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mControlID != 0)
					{
						mControlMessageQueue.addMessage(getControlID(), LEFT_MOUSE_BUTTON_CLICK, event);
					}
				}
			}
			mButtonPress = false;
		}
		break;
	case sf::Event::MouseMoved:
		//if (body.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		//{
		if (mMouseOver)
		{
			//mMouseOver = true;
			if (!mMouseEnter)
			{
				mControlMessageQueue.addMessage(getControlID(), MOUSE_ENTER, event);
				mMouseEnter = true;
				mMouseLeave = false;
			}
			if (mButtonPress)
			{
				mControlMessageQueue.addMessage(getControlID(), LEFT_MOUSE_BUTTON_DOWN, event);
			}
			mControlMessageQueue.addMessage(getControlID(), MOUSE_MOVE, event);
		}
		//}
		//else {
		else
		{
			if (!mMouseLeave)
			{
				mControlMessageQueue.addMessage(getControlID(), MOUSE_LEAVE, event);
				mMouseLeave = true;
				mMouseEnter = false;
			}
			if (mButtonPress)
			{
				mControlMessageQueue.addMessage(getControlID(), LEFT_MOUSE_BUTTON_DOWN, event);
			}
			//mMouseOver = false;
		}
		//}
		break;
	default:
		break;
	}

	for (int i = 0; i < mChildren.size(); i++)
	{
		mChildren.at(i)->events(event, window, callback);
	}

	//callback(*this, mControlMessageQueue);
	mCallBack(*this, mControlMessageQueue);
}

void Control::update() {
	/*if (mSize.x > 0 && mSize.y > 0 && mText.getString() != "")
	{
		while (mText.getGlobalBounds().width < mSize.x / 6 * 5 && mText.getGlobalBounds().height < mSize.y - 2.5f)
		{
			mText.setCharacterSize(mText.getCharacterSize() + 1);
		}
		if (mText.getGlobalBounds().width < mSize.x / 6 * 5 || mText.getGlobalBounds().height < mSize.y - 2.5f)
		{
			mText.setCharacterSize(mText.getCharacterSize() - 1);
		}
	}
	else
	{
		while (mText.getGlobalBounds().width > mSize.x / 6 * 5 && mText.getGlobalBounds().height > mSize.y - 2.5f)
		{
			mText.setCharacterSize(mText.getCharacterSize() - 1);
		}
		if (mText.getGlobalBounds().width > mSize.x / 6 * 5 || mText.getGlobalBounds().height > mSize.y - 2.5f)
		{
			mText.setCharacterSize(mText.getCharacterSize() + 1);
		}
	}

	mText.setOrigin(mText.getLocalBounds().left + mText.getLocalBounds().width / 2, mText.getLocalBounds().top + mText.getLocalBounds().height / 2);
	mText.setPosition(mSize.x / 2, mSize.y / 2);*/


	mText.setOrigin(0, 0);
	mSprite.setOrigin(0, 0);

	switch (mAlignment)
	{
	case TOP_LEFT_ALIGNMENT:
		//mText.setOrigin(mText.getLocalBounds().left + mText.getLocalBounds().width / 2, mText.getLocalBounds().top + mText.getLocalBounds().height / 2);
		mText.setPosition(0, 0);
		mSprite.setPosition(0, 0);
		break;
	case TOP_MIDDLE_ALIGNMENT:
		mText.setPosition((mSize.x / 2) - (mText.getLocalBounds().width / 2), 0);
		mSprite.setPosition((mSize.x / 2) - (mSprite.getLocalBounds().width / 2), 0);
		break;
	case TOP_RIGHT_ALIGNMENT:
		mText.setPosition(mSize.x - (mText.getLocalBounds().width) - 5.0f, 0);
		mSprite.setPosition(mSize.x - mSprite.getLocalBounds().width - 5.0f, 0);
		break;
	case MIDDLE_LEFT_ALIGNMENT:
		mText.setPosition(0, (mSize.y / 2) - (mText.getCharacterSize() / 2));
		mSprite.setPosition(0, (mSize.y / 2) - (mSprite.getLocalBounds().height / 2));
		break;
	case MIDDLE_MIDDLE_ALIGNMENT:
		mText.setPosition((mSize.x / 2) - (mText.getLocalBounds().width / 2), (mSize.y / 2) - (mText.getCharacterSize() / 2));
		mSprite.setPosition(((float)mSize.x / 2) - ((float)mSprite.getGlobalBounds().width / 2), ((float)mSize.y / 2) - ((float)mSprite.getGlobalBounds().height / 2));
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
		mText.setPosition(mSize.x  - mText.getLocalBounds().width - 5.0f, mSize.y - mText.getCharacterSize());
		break;
	default:
		break;
	}
}

void Control::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mBody, states);
	target.draw(mText, states);

	for (int i = 0; i < mChildren.size(); i++)
	{
		mChildren.at(i)->draw(target, states);
	}
}