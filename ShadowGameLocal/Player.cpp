#include "Player.hpp"
#include "Attributes.hpp"
//Kevin
Player::Player()
{
	m_username = "Default";
	m_password = "Default";
	setPosition(sf::Vector2f(20, 0));
	setScale(sf::Vector2f(0.078125, 0.078125));
	setColor(sf::Color::Red);
	
	m_texture.loadFromFile("aqua-ball.png");
	setTexture(m_texture);
	m_texture.setSmooth(true);
	m_keySet = 1;
}
Player::Player(std::string p_username, std::string p_password, sf::Vector2f p_position,
					sf::Vector2f p_scale, uint8_t p_keySet)
{
	m_username = p_username;
	m_password = p_password;
	setPosition(p_position);
	setScale(p_scale);
	//setColor(sf::Color::Magenta);

	m_texture.loadFromFile("aqua-ball.png");
	setTexture(m_texture);
	m_texture.setSmooth(true);
	m_keySet = p_keySet;
}

//Handle all player changes per update
void Player::Update(ShadowFactory p_shadowFactory)
{
	InputHandler(p_shadowFactory);
}

//Move the player by one square in a certain direction
void Player::Move(sf::Vector2f p_direction, ShadowFactory p_shadowFactory)
{	
	sf::Vector2f temp = getPosition();
	temp += p_direction;
	if (p_shadowFactory.doesCollideWithWorld(sf::FloatRect(temp.x, temp.y, 20, 20)))
		move(p_direction);
}


//Handle input from both players in splitscreen version of game by using two keysets @see Attributes.h
void Player::InputHandler(ShadowFactory p_shadowFactory)
{
	switch (m_keySet)
	{
	case 1:
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_LEFT]))
		{
			// left key is pressed: move our character
			Move(sf::Vector2f(-20, 0), p_shadowFactory);
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_RIGHT]))
		{
			// right key is pressed: move our character
			Move(sf::Vector2f(20, 0), p_shadowFactory);
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_DOWN]))
		{
			// down key is pressed: move our character
			Move(sf::Vector2f(0, 20), p_shadowFactory);
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_UP]))
		{
			// up key is pressed: move our character
			Move(sf::Vector2f(0, -20), p_shadowFactory);
		}
		break;
	case 2:
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_LEFT]))
		{
			// left key is pressed: move our character
			Move(sf::Vector2f(-20, 0), p_shadowFactory);
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_RIGHT]))
		{
			// right key is pressed: move our character
			Move(sf::Vector2f(20, 0), p_shadowFactory);
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_DOWN]))
		{
			// down key is pressed: move our character
			Move(sf::Vector2f(0, 20), p_shadowFactory);
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_UP]))
		{
			// up key is pressed: move our character
			Move(sf::Vector2f(0, -20), p_shadowFactory);
		}
		break;
	}
}
