#pragma once

#include "Image.h"
#include "Label.h"

class Button : public Window
{
public:
	Button(const std::string text = "", const std::string fontName = "Oswald-Light.ttf", const float fontSize = 10.0f);
	~Button();

	float getTextWidth();

	void setFont(const std::string fontName, const float fontSize);
	void setImage(const std::string imageName, const float sizeX, const float sizeY);
	void setImageAlignment(sf::Uint32 alignment);
	void setText(const std::string text);


private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void update();

	Image mImage;
	Label mLabel;
};