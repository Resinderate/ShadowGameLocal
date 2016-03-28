#include "Player.hpp"
#include "Attributes.hpp"
#include "VectorAlgebra2D.hpp"
//Kevin

Player::Player()
{
}

Player::Player(std::string p_username, std::string p_password, sf::Vector2f p_position, uint8_t p_keySet, std::vector<Animation> p_animations)
{
	m_username = p_username;
	m_password = p_password;
	setPosition(p_position);

	m_animations = p_animations;
	m_keySet = p_keySet;
	m_isDead = false;
	// Can set the inital pause or loops here too.
	setFrameTime(sf::seconds(0.4));

	play(m_animations[0]);
}

//Handle all player changes per update
void Player::Update(ShadowFactory p_shadowFactory, float p_delta, std::vector<Player> p_players)
{
	if (!m_isDead)
	{
		//InputHandler(p_shadowFactory, p_players);
		InputHandler(p_shadowFactory, p_delta, p_players);

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

void Player::Attack(std::vector<Player> p_players)
{
	for (Player p : p_players)
	{
		if (p.GetUsername() != this->GetUsername())
		{
			float len = thor::length(p.getPosition() - this->getPosition());
			Log(GetUsername() + " -> " + p.GetUsername() + " : " + std::to_string(len));
			if (thor::length(p.getPosition() - this->getPosition()) <= 20.f)
			{
				setColor(sf::Color::Green);
			}
		}
	}
}
void Player::Attack2(std::vector<Player> p_players)
{
	for (Player p : p_players)
	{
		if (p.GetUsername() != this->GetUsername())
		{
			if (thor::length(p.getPosition() - this->getPosition()) <= 20)
			{
				Log("Kill Blue");
				setColor(sf::Color::Blue);
			}
		}
	}
}

//Handle input from both players in splitscreen version of game by using two keysets @see Attributes.h
//void Player::InputHandler(ShadowFactory p_shadowFactory, std::vector<Player> p_players)
void Player::InputHandler(ShadowFactory p_shadowFactory, float p_delta, std::vector<Player> p_players)
{
	float moveAmount = 800;
	moveAmount *= p_delta;

	int up = 270;
	int down = 90;
	int right = 0;
	int left = 180;
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
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_ATTACK]))
		{
			// Attack key is pressed
			Attack2(p_players);
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
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_ATTACK]))
		{
			// Attack key is pressed
			Attack(p_players);
		}
		break;
	}
}
