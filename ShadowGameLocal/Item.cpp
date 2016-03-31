#include "Item.hpp"

Item::Item(sf::Vector2f p_position, ITEMTYPE p_type)
{
	m_type = p_type;
	setPosition(p_position);
	m_destroy = false;
	m_texture.loadFromFile("spritesheet/heart.png");
	this->setTexture(m_texture);
}