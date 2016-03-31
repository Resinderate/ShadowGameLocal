#include "Item.hpp"

Item::Item(sf::Vector2f p_position, ItemType p_type)
{
	m_type = p_type;
	setPosition(p_position);
}