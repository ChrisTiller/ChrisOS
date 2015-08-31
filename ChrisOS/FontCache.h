#pragma once
#include <SFML\Graphics.hpp>
#include <map>


class FontCache
{
public:
	FontCache();
	~FontCache();

	sf::Font getFont(std::string texturePath);

private:
	std::map<std::string, sf::Font> mFonts;
};