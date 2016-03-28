#include "Player.hpp"
#include "Attributes.hpp"
//Kevin

Player::Player(std::string p_username, std::string p_password, sf::Vector2f p_position, uint8_t p_keySet, std::vector<Animation> p_animations)
{
	m_username = p_username;
	m_password = p_password;
	setPosition(p_position);

	m_animations = p_animations;
	m_keySet = p_keySet;
	// Can set the inital pause or loops here too.
	setFrameTime(sf::seconds(0.4));

	play(m_animations[0]);
}

//Handle all player changes per update
void Player::Update(ShadowFactory p_shadowFactory, float p_delta)
{
	InputHandler(p_shadowFactory, p_delta);

	//float velocityCap = 1000.f;
	//if (m_velocity != sf::Vector2f() || thor::length(m_velocity) > velocityCap)
		//m_velocity = thor::unitVector(m_velocity) * velocityCap;

	float dragAmount = 4;
	float drag = 1 / (1 + (p_delta * dragAmount));
	if (m_velocity != sf::Vector2f())
		m_velocity = thor::unitVector(m_velocity) * (thor::length(m_velocity) * drag);

	Move(m_velocity * p_delta, p_shadowFactory);

	update(sf::seconds(p_delta));
}

//Move the player by one square in a certain direction
void Player::Move(sf::Vector2f p_direction, ShadowFactory p_shadowFactory)
{	
	sf::FloatRect player = getGlobalBounds();
	player.left += p_direction.x;
	player.top += p_direction.y;

	// Could do some more complicated movement here.
	if (!p_shadowFactory.doesCollideWithWorld(player))
	{
		move(p_direction);
		return;
	}
	player.top -= p_direction.y;
	if (!p_shadowFactory.doesCollideWithWorld(player))
	{
		move(sf::Vector2f(p_direction.x, 0));
		return;
	}
	player.top += p_direction.y;
	player.left -= p_direction.x;
	if (!p_shadowFactory.doesCollideWithWorld(player))
	{
		move(sf::Vector2f(0, p_direction.y));
		return;
	}
}


//Handle input from both players in splitscreen version of game by using two keysets @see Attributes.h
void Player::InputHandler(ShadowFactory p_shadowFactory, float p_delta)
{
	float moveAmount = 800;
	moveAmount *= p_delta;
	switch (m_keySet)
	{
	case 1:
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_LEFT]))
		{
			// left key is pressed: move our character
			m_velocity.x -= moveAmount;
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_RIGHT]))
		{
			// right key is pressed: move our character
			m_velocity.x += moveAmount;
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_DOWN]))
		{
			// down key is pressed: move our character
			m_velocity.y += moveAmount;
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_UP]))
		{
			// up key is pressed: move our character
			m_velocity.y -= moveAmount;
		}
		break;
	case 2:
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_LEFT]))
		{
			// left key is pressed: move our character
			m_velocity.x -= moveAmount;
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_RIGHT]))
		{
			// right key is pressed: move our character
			m_velocity.x += moveAmount;
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_DOWN]))
		{
			// down key is pressed: move our character
			m_velocity.y += moveAmount;
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_UP]))
		{
			// up key is pressed: move our character
			m_velocity.y -= moveAmount;
		}
		break;
	}
}
