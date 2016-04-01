// Written by: Ronan

#ifndef TEXTUREDWORLD_HPP
#define TEXTUREDWORLD_HPP

#include <vector>
#include <unordered_map>
#include "SFML\Graphics.hpp"
#include "Attributes.hpp"

class TexturedWorld
{
public:
	bool load();
	std::vector<sf::Sprite>& getTexturedWorld();

private:
	sf::Image m_tileSheet;
	std::unordered_map<std::string, sf::Texture> m_textureMap;
	std::vector<sf::Sprite> m_spriteTiles;
	
	bool loadTilesheet();
	bool loadTextures();
	bool loadSprites();
};
#endif