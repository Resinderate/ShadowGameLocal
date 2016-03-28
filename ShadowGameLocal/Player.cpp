#include "Player.hpp"
#include "Attributes.hpp"
#include "VectorAlgebra2D.hpp"
//Kevin
Player::Player()
{
	m_username = "Default";
	m_password = "Default";
	setPosition(sf::Vector2f(20, 0));
	//setScale(sf::Vector2f(0.078125, 0.078125));
	setColor(sf::Color::Red);
	
	m_texture.loadFromFile("spritesheet/hitman1_hold.png");
	setTexture(m_texture);
	m_texture.setSmooth(true);
	m_keySet = 1;
	m_isDead = false;
}
Player::Player(std::string p_username, std::string p_password, sf::Vector2f p_position, sf::Vector2f p_scale, uint8_t p_keySet)
{
	m_username = p_username;
	m_password = p_password;
	setPosition(p_position);
	//setScale(p_scale);
	//setColor(sf::Color::Magenta);

	m_texture.loadFromFile("spritesheet/hitman1_hold.png");
	setTexture(m_texture);
	m_texture.setSmooth(true);
	m_keySet = p_keySet;
	m_isDead = false;
}

//Handle all player changes per update
//void Player::Update(ShadowFactory p_shadowFactory, std::vector<Player> p_players)
void Player::Update(ShadowFactory p_shadowFactory, float p_delta)
{
	if (!m_isDead)
	{
	//InputHandler(p_shadowFactory, p_players);
	InputHandler(p_shadowFactory, p_delta);

	//float velocityCap = 1000.f;
	//if (m_velocity != sf::Vector2f() || thor::length(m_velocity) > velocityCap)
		//m_velocity = thor::unitVector(m_velocity) * velocityCap;

	float dragAmount = 4;
	float drag = 1 / (1 + (p_delta * dragAmount));
	if (m_velocity != sf::Vector2f())
		m_velocity = thor::unitVector(m_velocity) * (thor::length(m_velocity) * drag);

	Move(m_velocity * p_delta, p_shadowFactory);
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

//void Player::Attack(std::vector<Player> p_players)
//{
//	for (Player p : p_players)
//	{
//		if (p.GetUsername() != this->GetUsername())
//		{
//			if (thor::length(p.getPosition() - this->getPosition()) <= 20)
//			{
//				setColor(sf::Color::Green);
//			}
//		}
//	}
//}
//void Player::Attack2(std::vector<Player> p_players)
//{
//	for (Player p : p_players)
//	{
//		if (p.GetUsername() != this->GetUsername())
//		{
//			if (thor::length(p.getPosition() - this->getPosition()) <= 20)
//			{
//				setColor(sf::Color::Blue);
//			}
//		}
//	}
//}

//Handle input from both players in splitscreen version of game by using two keysets @see Attributes.h
//void Player::InputHandler(ShadowFactory p_shadowFactory, std::vector<Player> p_players)
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
			Move(sf::Vector2f(0, -20), p_shadowFactory);
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_ATTACK]))
		{
			// Attack key is pressed
		//	Attack2(p_players);
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
			Move(sf::Vector2f(0, -20), p_shadowFactory);
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_ATTACK]))
		{
			// Attack key is pressed
			//Attack(p_players);
		}
		break;
	}
}
