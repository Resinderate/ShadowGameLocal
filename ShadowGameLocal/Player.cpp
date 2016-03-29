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
	m_maxHealth = 250;
	m_health = m_maxHealth;
	m_score = 0;

	// Can set the inital pause or loops here too.
	setFrameTime(sf::seconds(0.4));

	play(m_animations[0]);

	hitB.loadFromFile("audio/hit.wav");
	hit.setBuffer(hitB);
	hit.setVolume(30);

	footB.loadFromFile("audio/foot.wav");
	foot.setBuffer(footB);
	foot.setVolume(30);
	foot.setLoop(true);

	setOrigin(m_animations[0].getFrame(0).width / 2, m_animations[0].getFrame(0).height / 2);

}

//Handle all player changes per update
void Player::Update(ShadowFactory p_shadowFactory, float p_delta, std::vector<Player> &p_players)
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

		//UpdateAnimations();

		update(sf::seconds(p_delta));	
	}
	else
	{
		m_isDead = false;
		setPosition(75, 25);
		m_health = m_maxHealth;
	}
}



//Move the player by one square in a certain direction
void Player::Move(sf::Vector2f p_direction, ShadowFactory p_shadowFactory)
{	
	sf::FloatRect player = GetCollisionBox();
	player.left += p_direction.x;
	player.top += p_direction.y;

	//if (isWalking)
	//{
	//	foot.play();
	//	isWalking = false;
	//}

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

void Player::Attack(std::vector<Player> &p_players)
{
	for (auto itr = p_players.begin(); itr < p_players.end(); itr++)
	{
		if (itr->GetUsername() != this->GetUsername())
		{
			Player& p = *itr;
			float len = thor::length(itr->getPosition() - this->getPosition());
			Log(GetUsername() + " -> " + itr->GetUsername() + " : " + std::to_string(len));
			if (thor::length(itr->getPosition() - this->getPosition()) <= 40.f && itr->GetHealth() > 0)
			{
				itr->GetHealth()--;
				Log(itr->GetUsername() + " -> Health" + " : " + std::to_string(itr->GetHealth()));
			
				hit.play();

				if (itr->GetHealth() <= 0)
				{
					itr->GetIsDead() = true;
					m_score++;
				}
			}
		}
	}
}

sf::FloatRect Player::GetCollisionBox()
{
	float size = 25;
	return sf::FloatRect(getPosition().x - size/2, getPosition().y - size/2, size, size);
}

void Player::UpdateAnimations()
{
	if (m_velocity != sf::Vector2f())
	{
		int rot = -1;
		int E = 0;
		int SE = 45;
		int S = 90;
		int SW = 135;
		int W = 180;
		int NW = 225;
		int N = 270;
		int NE = 315;

		// See what the velocity and change the dir of character.
		sf::Vector2f dir = thor::unitVector(m_velocity);

		// Update the animations if moving or stopped.

		// Might be able to do other animations here.
	}
}

//Handle input from both players in splitscreen version of game by using two keysets @see Attributes.h
//void Player::InputHandler(ShadowFactory p_shadowFactory, std::vector<Player> p_players)
void Player::InputHandler(ShadowFactory p_shadowFactory, float p_delta, std::vector<Player> &p_players)
{
	float moveAmount = 800;
	moveAmount *= p_delta;

	int rot = -1;
	int E = 0;
	int SE = 45;
	int S = 90;
	int SW = 135;
	int W = 180;
	int NW = 225;
	int N = 270;
	int NE = 315;

	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;

	switch (m_keySet)
	{
	case 1:
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_LEFT]))
		{
			// left key is pressed: move our character
			m_velocity.x -= moveAmount;
			left = true;
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_RIGHT]))
		{
			// right key is pressed: move our character
			m_velocity.x += moveAmount;
			right = true;
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_DOWN]))
		{
			// down key is pressed: move our character
			m_velocity.y += moveAmount;
			down = true;
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_UP]))
		{
			// up key is pressed: move our character
			m_velocity.y -= moveAmount;
			up = true;
		}
		if (sf::Keyboard::isKeyPressed(KeySet1[KEY_COMMAND_ATTACK]))
		{
			// Attack key is pressed
			Attack(p_players);
		}
		break;
	case 2:
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_LEFT]))
		{
			// left key is pressed: move our character
			m_velocity.x -= moveAmount;
			left = true;
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_RIGHT]))
		{
			// right key is pressed: move our character
			m_velocity.x += moveAmount;
			right = true;
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_DOWN]))
		{
			// down key is pressed: move our character
			m_velocity.y += moveAmount;
			down = true;
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_UP]))
		{
			// up key is pressed: move our character
			m_velocity.y -= moveAmount;
			up = true;
		}
		if (sf::Keyboard::isKeyPressed(KeySet2[KEY_COMMAND_ATTACK]))
		{
			// Attack key is pressed
			Attack(p_players);
		}
		break;
	}

	if (up && right)
		rot = NE;
	else if (up && left)
		rot = NW;
	else if (down && right)
		rot = SE;
	else if (down && left)
		rot = SW;
	else if (up)
		rot = N;
	else if (down)
		rot = S;
	else if (right)
		rot = E;
	else if (left)
		rot = W;

	if (rot != -1)
		setRotation(rot);
}
