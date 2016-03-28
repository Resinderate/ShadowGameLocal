#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SFML\Graphics.hpp"
#include "ShadowFactory.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
//Kevin
class Player : public AnimatedSprite
{
public:
	Player(std::string p_username, std::string p_password, sf::Vector2f p_position, uint8_t keySet, std::vector<Animation> p_animations);
	inline std::string& GetUsername() { return m_username; }
	inline std::string& GetPassword() { return m_password; }
	void Update(ShadowFactory p_shadowFactory, float p_delta);
	void Move(sf::Vector2f p_direction, ShadowFactory p_shadowFactory);
	void InputHandler(ShadowFactory p_shadowFactory, float p_delta);
private:		
	std::string m_username;
	std::string m_password;
	uint8_t m_keySet;

	sf::Vector2f m_velocity;
	std::vector<Animation> m_animations;
};

#endif