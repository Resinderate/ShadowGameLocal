#ifndef ITEM_HPP
#define ITEM_HPP

#include "SFML\Graphics.hpp"
#include "Attributes.hpp"

class Item : public sf::Sprite
{
public:
	Item(const Item& item);
	Item(sf::Vector2f p_position, ITEMTYPE p_type);
	inline bool &GetDestroy() { return m_destroy; }
private:
	ITEMTYPE m_type;
	bool m_destroy;
	sf::Texture m_texture;
};
#endif