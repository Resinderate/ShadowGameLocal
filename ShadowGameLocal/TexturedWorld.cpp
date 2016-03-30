#include "TexturedWorld.hpp"

bool TexturedWorld::load()
{
	if (!loadTilesheet())
		return false;
	if (!loadTextures())
		return false;
	if (!loadSprites())
		return false;
	return true;
}

std::vector<sf::Sprite>& TexturedWorld::getTexturedWorld()i
{
	return m_spriteTiles;
}

bool TexturedWorld::loadTilesheet()
{
	if (!m_tileSheet.loadFromFile("spritesheet/spritesheet.png"))
		return false;
	return true;
}

bool TexturedWorld::loadTextures()
{
	sf::Texture tex;
	for (auto s : TEXTURE_MAPPINGS)
	{
		if (!tex.loadFromImage(m_tileSheet, s.second))
			return false;
		m_textureMap.insert(std::pair<std::string, sf::Texture>(s.first, tex));
	}
	return true;
}

bool TexturedWorld::loadSprites()
{
	sf::Sprite spr;
	int tileSize = 64;

	sf::Image texWorld;
	if (!texWorld.loadFromFile("maps/texturemap.png"))
		return false;

	auto size = texWorld.getSize();
	std::string texID = "";

	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			// Check for the colors.
			for (auto col : COLOR_MAPPINGS)
			{
				if (texWorld.getPixel(i, j) == col.first)
				{
					texID = col.second;
					spr.setTexture(m_textureMap[texID]);
					spr.setPosition(i * tileSize, j * tileSize);
					m_spriteTiles.push_back(spr);
					break;
				}
			}
		}
	}

	return true;
}
