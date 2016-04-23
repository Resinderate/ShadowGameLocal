#include "PlayerDatabase.hpp"

PlayerDatabase::PlayerDatabase()
{
	m_players = std::vector<Player>();
}

bool PlayerDatabase::AddPlayer(Player &p_player){
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

bool PlayerDatabase::RemovePlayer(Player &p_player) {
	for (auto itr = m_players.begin(); itr < m_players.end(); itr++)
	{
		if (itr->GetUsername() == p_player.GetUsername())
		{
			m_players.erase(itr);
			return true;
		}
	}
	return false;
}

void PlayerDatabase::Update(ShadowFactory p_shadowFactory, float p_delta, std::vector<Item>& p_items)
{
	for (auto itr = m_players.begin(); itr < m_players.end(); itr++)
	{
		itr->Update(p_shadowFactory, p_delta, m_players, p_items);
	}
}