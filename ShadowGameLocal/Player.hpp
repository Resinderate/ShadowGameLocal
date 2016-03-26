#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SFML\Graphics.hpp"
#include "ShadowFactory.hpp"
//Kevin
class Player : public sf::Sprite
{
public:
	Player();
	Player(std::string p_username, std::string p_password, sf::Vector2f p_position, sf::Vector2f p_scale, uint8_t keySet);
	inline std::string& GetUsername() { return m_username; }
	inline std::string& GetPassword() { return m_password; }
	void Update();
	void Move(sf::Vector2f p_direction);
	void InputHandler();
private:		
	std::string m_username;
	std::string m_password;
	sf::Texture m_texture;
	uint8_t m_keySet;
};

#endif