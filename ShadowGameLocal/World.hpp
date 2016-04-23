#ifndef WORLD_HPP
#define WORLD_HPP

#include "ItemDatabase.hpp"
#include "PlayerDatabase.hpp"


class World
{
public:

	World();
	void Update(ShadowFactory p_shadowFactory, float p_delta);
	void AddPlayer(Player &p_player);
	void RemovePlayer(Player &p_player);
	void AddItem(Item &p_item);
	inline ItemDatabase &GetItemDatabase() { return m_itemDB; };
	inline PlayerDatabase &GetPlayerDatabase() { return m_playerDB; };

private:
	ItemDatabase m_itemDB;
	PlayerDatabase m_playerDB;

};

#endif // !WORLD_HPP
