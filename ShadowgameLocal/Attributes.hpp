#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
#include "SFML\Window.hpp"
#include <cstdint>

const uint8_t KEY_COMMAND_UP = 0;
const uint8_t KEY_COMMAND_DOWN = 1;
const uint8_t KEY_COMMAND_LEFT = 2;
const uint8_t KEY_COMMAND_RIGHT = 3;
const sf::Keyboard::Key KeySet1[4] = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right };
const sf::Keyboard::Key KeySet2[4] = { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D };

#endif
