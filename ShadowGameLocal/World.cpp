#include "World.hpp"

World::World()
{

}

void World::AddPlayer(Player &p_player)
{
	m_playerDB.AddPlayer(p_player);
}

void World::RemovePlayer(Player &p_player)
{
	m_playerDB.RemovePlayer(p_player);
}

void World::AddItem(Item &p_item)
{
	m_itemDB.AddItem(p_item);
}

void World::Update(ShadowFactory p_shadowFactory, float p_delta)
{
	m_itemDB.Update(p_shadowFactory, p_delta);
	m_playerDB.Update(p_shadowFactory, p_delta, m_itemDB.GetItems());
}