#ifndef ITEM_HPP
#define ITEM_HPP

#include "SFML\Graphics.hpp"
#include "Attributes.hpp"

class Item : public sf::Sprite
{
public:
	Item(sf::Vector2f p_position, ItemType p_type);
private:
	ItemType m_type;
};
#endif