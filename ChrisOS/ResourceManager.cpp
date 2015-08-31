#include "ResourceManager.h"


TextureCache ResourceManager::mTextureCache;
FontCache ResourceManager::mFontCache;

std::string ResourceManager::mFontPath = "Resources\\Fonts\\";
std::string ResourceManager::mTexturePath = "Resources\\Images\\";

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

sf::Texture& ResourceManager::getTexture(const std::string& textureName)
{
	return *mTextureCache.getTexture(mTexturePath + textureName);
}

sf::Font ResourceManager::getFont(std::string fontName)
{
	return mFontCache.getFont(mFontPath + fontName);
}