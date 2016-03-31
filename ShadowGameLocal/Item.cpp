#include "Item.hpp"

Item::Item(const Item & item)
{
	m_type = item.m_type;
	setPosition(item.getPosition());
	m_destroy = item.m_destroy;
	m_texture = item.m_texture;
	setTexture(m_texture);
}

Item::Item(sf::Vector2f p_position, ITEMTYPE p_type)
{
	m_type = p_type;
	setPosition(p_position);
	m_destroy = false;
	m_texture.loadFromFile("spritesheet/heart.png");
	setTexture(m_texture);
}