#include "TexturedWorld.hpp"

bool TexturedWorld::load()
{
	loadTilesheet();
	loadTextures();
	loadSprites();
	return false;
}

bool TexturedWorld::loadTilesheet()
{
	m_tileSheet = sf::Image();
	m_tileSheet.loadFromFile("somefile.png");

	// error checking pls.
}

bool TexturedWorld::loadTextures()
{
	// Load the textures needed from the tilesheet. Give them names to use in the Sprite loading phase.
	return false;
}

bool TexturedWorld::loadSprites()
{
	// Check all the colors of the map thing and create sprites based on it.
	return false;
}
