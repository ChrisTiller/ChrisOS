#pragma once
#include <SFML\Graphics.hpp>

#include "Window.h"

class Image : public Window
{
public:
	Image();
	Image(const std::string &imageName, const float sizeX, const float sizeY);

	~Image();

	sf::Uint32 getAlignment();
	sf::Vector2f getImagePosition();
	sf::Vector2f getImageSize();

	
	void setImage(const std::string &imageName);
	void setImage(const std::string &imageName, const float sizeX, const float sizeY);
	void setImageAlignment(const sf::Uint32 alignment);
	void setImagePosition(const float x, const float y);
	void setImagePosition(const sf::Vector2f position);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:

	void update();

	sf::Uint32 mAlignment;
			
	// holds the image size
	sf::Vector2f mImageSize;
	sf::Vector2f mSize;
	// holds the image (sprite)
	sf::Sprite mImage;

	static std::string ImageDir;

};