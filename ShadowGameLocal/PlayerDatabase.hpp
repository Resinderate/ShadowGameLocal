#ifndef PLAYERDATABASE_HPP
#define PLAYERDATABASE_HPP

#include "Player.hpp"
#include "Attributes.hpp"
#include <vector>

class PlayerDatabase
{
public:
	PlayerDatabase();
	bool AddPlayer(Player &p_player);
	inline std::vector<Player> &GetPlayers() { return m_players; }
private:
	std::vector<Player> m_players;
};

#endif

