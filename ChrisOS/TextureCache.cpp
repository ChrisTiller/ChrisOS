#include "TextureCache.h"


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
	for (auto it = mTextures.begin(); it != mTextures.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
}

sf::Texture* TextureCache::getTexture(const std::string& texturePath)
{
	auto it = mTextures.find(texturePath);

	if (it == mTextures.end())
	{
		sf::Texture* newTexture = new sf::Texture;
			
		if (newTexture->loadFromFile(texturePath));
		{
			mTextures.insert(std::make_pair(texturePath, newTexture));
		}

		return newTexture;
	}
	return it->second;
}