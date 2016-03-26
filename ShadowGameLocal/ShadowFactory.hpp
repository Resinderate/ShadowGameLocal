#ifndef SHADOWFACTORY_HPP
#define SHADOWFACTORY_HPP

#include <vector>
#include "SFML\Graphics.hpp"
#include "Line.hpp"
#include "VectorAlgebra2D.hpp"
#include "Log.h"

class ShadowFactory
{
public:
	static std::vector<sf::VertexArray> getShadows(sf::Vector2f playerPosition, sf::Color color);
	static bool load();
	static bool doesCollideWithWorld(sf::FloatRect p_bounds);

private:
	static std::vector<sf::FloatRect> shadowCasters;

	static std::vector<Line> getShadowLines();
};
#endif