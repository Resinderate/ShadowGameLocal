#ifndef WORLD_HPP
#define WORLD_HPP

#include "ItemDatabase.hpp"
#include "PlayerDatabase.hpp"


class World
{
public:

	World();
	void Update();
	void AddPlayer(Player &p_player);
	void RemovePlayer(Player &p_player);
	void AddItem(Item &p_item);
	void RemoveItem(Item &p_item);

private:
	ItemDatabase m_itemDB;
	PlayerDatabase m_playerDB;

};

#endif // !WORLD_HPP
