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
	std::vector<sf::VertexArray> getShadows(sf::Vector2f playerPosition, sf::Color color);
	bool load();
	bool doesCollideWithWorld(sf::FloatRect p_bounds);

private:
	std::vector<sf::FloatRect> shadowCasters;

	std::vector<Line> getShadowLines();
	void optimizeShadowCasters();
};
#endif