#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SFML\Graphics.hpp"
#include "ShadowFactory.hpp"
#include <vector>
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "SFML\Audio.hpp"
//Kevin
class Player : public AnimatedSprite
{
public:
	Player();
	Player(std::string p_username, std::string p_password, sf::Vector2f p_position, uint8_t keySet, std::vector<Animation> p_animations);
	inline std::string &GetUsername() { return m_username; }
	inline std::string &GetPassword() { return m_password; }
	inline std::uint8_t &GetHealth() { return m_health; }
	inline bool &GetIsDead() { return m_isDead; }
	inline std::uint8_t SetHealth(int8_t p_val) { m_health = p_val; }
	inline std::uint8_t &GetMaxHealth() { return m_maxHealth; }
	inline std::uint8_t &GetScore() { return m_score; }
	void Update(ShadowFactory p_shadowFactory, float p_delta, std::vector<Player>& p_players);
	void Move(sf::Vector2f p_direction, ShadowFactory p_shadowFactory);
	void InputHandler(ShadowFactory p_shadowFactory, float p_delta, std::vector<Player>& p_players);

	void Attack(std::vector<Player> &p_players);
	sf::FloatRect GetCollisionBox();

private:		
	std::string m_username;
	std::string m_password;
	uint8_t m_keySet;
	uint8_t m_health;
	uint8_t m_maxHealth;
	uint8_t m_score;
	float m_attackDelay;
	float m_timeSinceLastAttack;
	bool m_isDead;

	sf::SoundBuffer hitB;
	sf::Sound hit;
	sf::SoundBuffer footB;
	sf::Sound foot;

	sf::Vector2f m_velocity;
	std::vector<Animation> m_animations;

	void UpdateAnimations();
};

#endif