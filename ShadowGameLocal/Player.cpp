#include "Player.hpp"
//Kevin
Player::Player()
{
	m_username = "Default";
	m_password = "Default";
	setPosition(sf::Vector2f(0, 0));
	setScale(sf::Vector2f(1, 1));
	setColor(sf::Color::Magenta);
	
	sf::Texture texture;
	texture.loadFromFile("aqua-ball.png", sf::IntRect(10, 10, 20, 20));
	setTexture(texture);
}
Player::Player(std::string p_username, std::string p_password, sf::Vector2f p_position,
					sf::Vector2f p_scale)
{
	m_username = "Default";
	m_password = "Default";
	setPosition(sf::Vector2f(0, 0));
	setScale(p_scale);
	setColor(sf::Color::Magenta);
}
