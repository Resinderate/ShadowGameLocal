#include "PlayerDatabase.hpp"

PlayerDatabase::PlayerDatabase()
{
	m_players = std::vector<Player>(10);
}

bool PlayerDatabase::AddPlayer(Player p_player){
	for (Player p : m_players)
	{
		if (p.GetUsername() == p_player.GetUsername())
		{
			return false;
		}
	}
	m_players.push_back(p_player);
	return true;
}