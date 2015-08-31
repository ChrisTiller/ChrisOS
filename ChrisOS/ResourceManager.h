#pragma once
#include "TextureCache.h"
#include "FontCache.h"


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static sf::Texture& getTexture(const std::string& textureName);
	static sf::Font getFont(std::string fontName);

private:
	static TextureCache mTextureCache;
	static FontCache mFontCache;

	static std::string mTexturePath;
	static std::string mFontPath;
};