#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
#include "SFML\Window.hpp"
#include <cstdint>
#include <unordered_map>

const uint8_t KEY_COMMAND_UP = 0;
const uint8_t KEY_COMMAND_DOWN = 1;
const uint8_t KEY_COMMAND_LEFT = 2;
const uint8_t KEY_COMMAND_RIGHT = 3;
const uint8_t KEY_COMMAND_ATTACK = 4;
const uint8_t NO_OF_KEYS = 5;
const uint8_t MAXIMUM_PLAYERS = 10;

const sf::Keyboard::Key KeySet1[NO_OF_KEYS] = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::RControl };
const sf::Keyboard::Key KeySet2[NO_OF_KEYS] = { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space };


const std::unordered_map<std::string, sf::IntRect> TEXTURE_MAPPINGS = { 
	{ "grass1", sf::IntRect(198, 0, 64, 64) },
	{ "grass2", sf::IntRect(396, 0, 64, 64) },
	{ "grass3", sf::IntRect(330, 132, 64, 64) },
	{ "grass4", sf::IntRect(330, 66, 64, 64) },
	{ "dirt1", sf::IntRect(330, 0, 64, 64) },
	{ "dirt2", sf::IntRect(264, 132, 64, 64) },
	{ "stone1", sf::IntRect(264, 66, 64, 64) },
	{ "stone2", sf::IntRect(264, 0, 64, 64) },
	{ "stone3", sf::IntRect(198, 132, 64, 64) },
	{ "stone4", sf::IntRect(198, 66, 64, 64) },
	{ "checkerGray", sf::IntRect(396, 66, 64, 64) },
	{ "checkerWhite", sf::IntRect(132, 132, 64, 64) },
	{ "checkerBrown", sf::IntRect(132, 66, 64, 64) },
	{ "checkerBrownAlt", sf::IntRect(132, 0, 64, 64) },
	{ "wood1", sf::IntRect(66, 132, 64, 64) },
	{ "wood2", sf::IntRect(66, 66, 64, 64) },
	{ "wood3", sf::IntRect(66, 0, 64, 64) },
	{ "wood4", sf::IntRect(0, 132, 64, 64) },
	{ "wood5", sf::IntRect(0, 66, 64, 64) },
	{ "wood6", sf::IntRect(0, 0, 64, 64) }
};

const std::vector<std::pair<sf::Color, std::string>> COLOR_MAPPINGS = {
	{ sf::Color(212, 157, 104, 255), "wood1"},
	{ sf::Color(39, 174, 96, 255), "grass1" },
	{ sf::Color(156, 192, 194, 255), "stone1" }
};

#endif
