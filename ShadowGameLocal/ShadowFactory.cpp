#include "ShadowFactory.hpp"

std::vector<sf::FloatRect> ShadowFactory::shadowCasters = std::vector<sf::FloatRect>();


std::vector<sf::VertexArray> ShadowFactory::getShadows(sf::Vector2f playerPosition, sf::Color color)
{
	auto lines = getShadowLines();
	std::vector<sf::VertexArray> shadows(lines.size());

	for (auto l : lines)
	{
		if (playerPosition == l.start || playerPosition == l.end)
			continue;

		sf::VertexArray shadow(sf::TrianglesStrip, 4);
		float shadowLength = 30;

		// Set the color
		for (int i = 0; i < shadow.getVertexCount(); i++)
		{
			shadow[i].color = color;
		}

		shadow[0].position = l.start;
		shadow[1].position = l.end;

		sf::Vector2f startDir = l.start - playerPosition;
		sf::Vector2f endDir = l.end - playerPosition;

		thor::unitVector(startDir);
		thor::unitVector(endDir);
	
		shadow[2].position = l.start + startDir * shadowLength;
		shadow[3].position = l.end + endDir * shadowLength;

		shadows.push_back(shadow);
	}

	return shadows;
}

bool ShadowFactory::load()
{
	// Might be able to perform some optimizations here.
	float rectSize = 20;

	sf::Image map;
	if (!map.loadFromFile("shadowmap.png"))
		return false;
	
	auto size = map.getSize();

	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{			
			if (map.getPixel(i, j) == sf::Color::Black)
			{
				shadowCasters.push_back(sf::FloatRect(i * rectSize, j * rectSize, rectSize, rectSize));
			}
		}
	}	

	return true;
}

bool ShadowFactory::doesCollideWithWorld(sf::FloatRect p_bounds)
{
	for (auto s : shadowCasters)
	{
		if (s.intersects(p_bounds))
		{
			return false;
		}
	}
	return true;
}

std::vector<Line> ShadowFactory::getShadowLines()
{
	// 4 lines in each rect.
	std::vector<Line> lines(shadowCasters.size() * 4);

	for (auto r : shadowCasters)
	{
		lines.push_back(Line(sf::Vector2f(r.left, r.top), sf::Vector2f(r.left + r.width, r.top)));
		lines.push_back(Line(sf::Vector2f(r.left + r.width, r.top), sf::Vector2f(r.left + r.width, r.top + r.height)));
		lines.push_back(Line(sf::Vector2f(r.left + r.width, r.top + r.height), sf::Vector2f(r.left, r.top + r.height)));
		lines.push_back(Line(sf::Vector2f(r.left, r.top + r.height), sf::Vector2f(r.left, r.top)));
	}

	return lines;
}
