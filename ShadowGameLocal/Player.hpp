#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SFML\Graphics.hpp"
//Kevin
class Player : public sf::Sprite
{
public:
	Player();
	Player(std::string p_username, std::string p_password, sf::Vector2f p_position, sf::Vector2f p_scale);
	inline std::string& GetUsername() { return m_username; }
	inline std::string& GetPassword() { return m_password; }
private:		
	std::string m_username;
	std::string m_password;
};

#endif