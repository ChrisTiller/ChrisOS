#pragma once

#include "Window.h"

class Label : public Window
{
public:
	Label(const std::string text = "", const std::string font = "Oswald-Light.ttf", const float fontSize = 10.0f, sf::Uint32 alignment = MIDDLE_MIDDLE_ALIGNMENT);
	~Label();

	sf::Color getTextColor();
	sf::Uint32 getAlignment();
	std::string getFontName();
	float getFontSize();

	void setAlignment(sf::Uint32 alignmet);
	void setFont(const std::string font);
	void setTextColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha = 255);
	void setText(const std::string text);
	void setFontSize(float size);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:


	void update();

	sf::Uint32 mAlignment;

	sf::Font mFont;
	sf::Text mText;

};

