#include "Player.hpp"
//Kevin
Player::Player()
{
	m_username = "Default";
	m_password = "Default";
	setPosition(sf::Vector2f(0, 0));
	setScale(sf::Vector2f(0.078125, 0.078125));
	//setColor(sf::Color::Magenta);
	
	m_texture.loadFromFile("aqua-ball.png");
	setTexture(m_texture);
	m_texture.setSmooth(true);
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
