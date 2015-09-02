#include "FontCache.h"


FontCache::FontCache()
{
}


FontCache::~FontCache()
{
	for (auto it = mFonts.begin(); it != mFonts.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
}

sf::Font* FontCache::getFont(std::string fontPath)
{
	auto it = mFonts.find(fontPath);

	if (it == mFonts.end())
	{
		sf::Font *newFont = new sf::Font;

		if (newFont->loadFromFile(fontPath))
		{
			mFonts.insert(std::make_pair(fontPath, newFont));
		}

		return newFont;
	}
	return it->second;
}