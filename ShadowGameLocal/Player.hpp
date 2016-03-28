#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SFML\Graphics.hpp"
#include "ShadowFactory.hpp"
#include <vector>
//Kevin
class Player : public sf::Sprite
{
public:
	Player();
	Player(std::string p_username, std::string p_password, sf::Vector2f p_position, sf::Vector2f p_scale, uint8_t keySet);
	
	void Update(ShadowFactory p_shadowFactory, std::vector<Player> p_players);
	void Move(sf::Vector2f p_direction, ShadowFactory p_shadowFactory);
	void InputHandler(ShadowFactory p_shadowFactory, std::vector<Player> p_players);
	void Attack(std::vector<Player> p_players);
	void Attack2(std::vector<Player> p_players);

	inline std::string& GetUsername() { return m_username; }
	inline std::string& GetPassword() { return m_password; }
	inline uint8_t& GetHealth() { return m_health; }
	inline bool& checkIsDead() { return m_isDead; }

private:		
	std::string m_username;
	std::string m_password;
	sf::Texture m_texture;
	uint8_t m_keySet;
	uint8_t m_health;
	bool m_isDead;

};

#endif