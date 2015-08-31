#include "FontCache.h"


FontCache::FontCache()
{
}


FontCache::~FontCache()
{
}

sf::Font FontCache::getFont(std::string fontPath)
{
	auto it = mFonts.find(fontPath);

	if (it == mFonts.end())
	{
		sf::Font newFont;
		newFont.loadFromFile(fontPath);

		mFonts.insert(std::make_pair(fontPath, newFont));

		return newFont;
	}
	return it->second;
}