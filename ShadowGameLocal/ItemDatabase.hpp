// Written by: Kevin

#ifndef ITEMDATABASE_HPP
#define ITEMDATABASE_HPP

#include "Item.hpp" 
#include "Attributes.hpp"
#include "ShadowFactory.hpp"
#include <vector>

class ItemDatabase
{
public:
	ItemDatabase();
	bool AddItem(Item &p_item);
	void Update(ShadowFactory p_shadowFactory, float p_delta);
	void PlaceRandom(ShadowFactory p_shadowFactory);
	inline std::vector<Item> &GetItems() { return m_items; }
private:
	std::vector<Item> m_items;
	float m_spawnTime;
	float m_lastSpawnTime;
};

#endif // !ITEMDATABASE_HPP

