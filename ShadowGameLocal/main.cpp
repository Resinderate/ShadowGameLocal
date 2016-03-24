#include <SFML/Graphics.hpp>
#include "VectorAlgebra2D.hpp"

sf::VertexArray getShadow(sf::Vector2f player, sf::Vector2f lineStart, sf::Vector2f lineEnd, sf::Color color);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::Vector2f start(400, 250);
	sf::Vector2f mid(400, 300);
	sf::Vector2f end(450, 300);

	sf::Vector2f player(0, 0);


	sf::VertexArray shadow1;
	sf::VertexArray shadow2;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseMoved)
			{
				player.x = event.mouseMove.x;
				player.y = event.mouseMove.y;
			}
		}

		//update
		shadow1 = getShadow(player, start, mid, sf::Color(255, 255, 0, 120));
		shadow2 = getShadow(player, mid, end, sf::Color(0, 0, 255, 120));

		window.clear();
		window.draw(shadow1);
		window.draw(shadow2);
		window.display();
	}

	return 0;
}

sf::VertexArray getShadow(sf::Vector2f player, sf::Vector2f lineStart, sf::Vector2f lineEnd, sf::Color color)
{
	sf::VertexArray shadow(sf::TrianglesStrip, 4);
	float shadowLength = 1000;

	for (int i = 0; i < shadow.getVertexCount(); i++)
	{
		shadow[i].color = color;
	}

	shadow[0].position = lineStart;
	shadow[1].position = lineEnd;
	// 2 is the projected Start point
	// 3 is the projected End point.
	
	sf::Vector2f startDir = lineStart - player;
	sf::Vector2f endDir = lineEnd - player;

	thor::unitVector(startDir);
	thor::unitVector(endDir);

	sf::Vector2f startProj =  startDir * shadowLength;
	sf::Vector2f endProj = endDir * shadowLength;

	shadow[2].position = startProj;
	shadow[3].position = endProj;

	return shadow;
}