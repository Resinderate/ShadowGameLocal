// Written by: Kevin

#ifndef PLAYERDATABASE_HPP
#define PLAYERDATABASE_HPP

#include "Player.hpp"
#include "Attributes.hpp"
#include <vector>

class PlayerDatabase
{
public:
	PlayerDatabase();
	void Update(ShadowFactory p_shadowFactory, float p_delta, std::vector<Item>& p_items);
	bool AddPlayer(Player &p_player);
	inline std::vector<Player> &GetPlayers() { return m_players; }
private:
	std::vector<Player> m_players;
};

#endif

