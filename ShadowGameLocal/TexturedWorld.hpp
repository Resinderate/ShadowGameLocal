#ifndef TEXTUREDWORLD_HPP
#define TEXTUREDWORLD_HPP

#include <vector>
#include "SFML\Graphics.hpp"

class TexturedWorld
{
public:
	bool load();
	std::vector<sf::Sprite> getTexturedWorld();

private:
	sf::Image m_tileSheet;
	std::vector<sf::Sprite> m_tiles;
	std::vector<sf::Texture> m_textures;

	bool loadTilesheet();
	bool loadTextures();
	bool loadSprites();
};
#endif