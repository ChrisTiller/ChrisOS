#include "Image.h"
#include "System.h"

std::string Image::ImageDir = "Resources\\Images\\";

Image::Image()
{

}

Image::Image(const std::string &imageName, const float sizeX, const float sizeY)
{
	setImage(imageName, sizeX, sizeY);
	setBackgroundColor(255, 255, 255, 0);
}

Image::~Image()
{
}


sf::Uint32 Image::getAlignment()
{
	return mAlignment;
}

sf::Vector2f Image::getImagePosition()
{
	return mImage.getPosition();
}

sf::Vector2f Image::getImageSize()
{
	return mImageSize;
}

void Image::setImage(const std::string &imageName)
{
	mImage.setTexture(ResourceManager::getTexture(imageName));
}

void Image::setImage(const std::string &imageName, const float sizeX, const float sizeY)
{
	mImage.setTexture(ResourceManager::getTexture(imageName));
	mImageSize = sf::Vector2f(sizeX, sizeY);
}

void Image::setImageAlignment(const sf::Uint32 alignment)
{
	mAlignment = alignment;
	//update();
}

void Image::setImagePosition(sf::Vector2f position)
{
	setImagePosition(position.x, position.y);
}

void Image::setImagePosition(const float x, const float y)
{
	sf::Vector2f newSize = sf::Vector2f(x / System::getInternalResolution().x * System::getWindow().getSize().x, y / System::getInternalResolution().y * System::getWindow().getSize().y);
	mImage.setPosition(newSize.x, newSize.y);
}

void Image::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBody, states);
	target.draw(mImage, states);
}

void Image::update()
{
	//mImage.setOrigin(0, 0);

	switch (mAlignment)
	{
	case TOP_LEFT_ALIGNMENT:
		mImage.setPosition(0, 0);
		break;
	case TOP_MIDDLE_ALIGNMENT:
		mImage.setPosition(((float)getImageSize().x / 2), 0);
		break;
	case TOP_RIGHT_ALIGNMENT:
		mImage.setPosition(mSize.x - (float)getImageSize().x - 5.0f, 0);
		break;
	case MIDDLE_LEFT_ALIGNMENT:
		mImage.setPosition(0, (mSize.y / 2) - ((float)getImageSize().y / 2));
		break;
	case MIDDLE_MIDDLE_ALIGNMENT:
		mImage.setPosition((getSize().x / 2 ) - ((float)getImageSize().x / 2), ((float)getImageSize().y / 2));
		break;
	case MIDDLE_RIGHT_ALIGNMENT:
		mImage.setPosition(mSize.x - ((float)getImageSize().x) - 5.0f, (mSize.y / 2) - ((float)getImageSize().y / 2));
		break;
	case BOTTOM_LEFT_ALIGNMENT:
		mImage.setPosition(0, mSize.y - (float)getImageSize().y);
		break;
	case BOTTOM_MIDDLE_ALIGNMENT:
		mImage.setPosition((mSize.x / 2) - ((float)getImageSize().x / 2), mSize.y - (float)getImageSize().y);
		break;
	case BOTTOM_RIGHT_ALIGNMENT:
		mImage.setPosition(mSize.x - (float)getImageSize().x - 5.0f, mSize.y - (float)getImageSize().y);
		break;
	default:
		break;
	}
}