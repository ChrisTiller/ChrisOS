#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <functional>
#include "ResourceManager.h"
#include "MessageQueue.h"


class Control;

//typedef void(*function)(Control &control, MessageQueue * messageQueue);
typedef void(*function)(Control &control, MessageQueue &messageQueue);

//enum ALIGNMENT
//{
//	TOP_LEFT_ALIGNMENT,
//	TOP_MIDDLE_ALIGNMENT,
//	TOP_RIGHT_ALIGNMENT,
//	MIDDLE_LEFT_ALIGNMENT,
//	MIDDLE_MIDDLE_ALIGNMENT,
//	MIDDLE_RIGHT_ALIGNMENT,
//	BOTTOM_LEFT_ALIGNMENT,
//	BOTTOM_MIDDLE_ALIGNMENT,
//	BOTTOM_RIGHT_ALIGNMENT
//};

class Control : public sf::Drawable, public sf::Transformable
{
public:
Control();
Control(const sf::Vector2f size);
~Control();

void addChildControl(Control &child);

uint getControlID();
void setControlID(uint ID);

void setCallBack(::function callback);

void setAlignment(uint alignmet);
void setBackgroundColor(const sf::Color &backgroundColor);
void setFont(sf::Font &font);
void setFont(const std::string font);
void setMouseOverBackgroundColor(const sf::Color &backgroundColor);
void setMouseOverOutlineColor(const sf::Color &outlineColor);
void setMouseOverTextColor(const sf::Color &textColor);
void setOutlineColor(const sf::Color &outlineColor);
void setOutlineThickness(const float thickness);
void setParent(Control &child);
void setControlPosition(float x, float y);
void setSize(const sf::Vector2f size);
void setSprite(const std::string texturePath);
void setString(const std::string str);
void setTextColor(const sf::Color &textColor);
void setTextSize(float size);

void events(sf::Event &event, sf::RenderWindow &window, function callback);

private:
virtual void update();
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

bool mMouseOver;
bool mMouseEnter;
bool mMouseLeave;
bool mButtonPress;

uint mControlID;
int mNumControls;

uint mAlignment;
uint mTextSize;

sf::Vector2f mSize;
sf::RectangleShape mBody;
sf::Font mFont;
sf::Text mText;
sf::Sprite mSprite;

//Colors
sf::Color mBackgroundColor;
sf::Color mMouseOverBackgroundColor;
sf::Color mTextColor;
sf::Color mMouseOverTextColor;
sf::Color mOutlineColor;
sf::Color mMouseOverOutlineColor;


// message queue for a control used for children controls to send parent messages
MessageQueue mControlMessageQueue;

// vector of pointers to children controls
std::vector<Control*> mChildren;

// pointer to a parent control
Control* mParent;
::function mCallBack;
};