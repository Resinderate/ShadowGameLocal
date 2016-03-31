#include "ItemDatabase.hpp"
#include <random>

ItemDatabase::ItemDatabase()
{
	 m_items = std::vector<Item>();
	 m_spawnTime = PICKUP_SPAWN_TIME;
	 m_lastSpawnTime = 0;
}

bool ItemDatabase::AddItem(Item &p_item)
{
	m_items.push_back(p_item);
	return true;
}

void ItemDatabase::Update(ShadowFactory p_shadowFactory, float p_delta)
{
	for (auto itr = m_items.begin(); itr < m_items.end(); itr++)
	{
		if (itr->GetDestroy())
		{
			m_items.erase(itr);
			break;
		}
	}
	m_lastSpawnTime += p_delta;
	if (m_lastSpawnTime > m_spawnTime)
	{
		PlaceRandom(p_shadowFactory);
		m_lastSpawnTime = 0;
	}
}

void ItemDatabase::PlaceRandom(ShadowFactory p_shadowFactory)
{
	sf::FloatRect rect;
	float x;
	float y;
	do {
		x = (rand() % 1600) + 1;
		y = (rand() % 1120) + 1;

		rect = sf::FloatRect(x, y, 35, 35);
	} while (p_shadowFactory.doesCollideWithWorld(rect));
	
	Item t = Item(sf::Vector2f(x, y), ITEMTYPE::HEALTHPICKUP);
	m_items.push_back(t);
}