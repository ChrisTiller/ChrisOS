#pragma once
#include <SFML\Graphics.hpp>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	sf::Texture* getTexture(const std::string& texturePath);

private:
	std::map<std::string, sf::Texture*> mTextures;
};
