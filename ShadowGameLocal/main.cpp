#include "SFML/Graphics.hpp"
#include "VectorAlgebra2D.hpp"
#include "ShadowFactory.hpp"
#include "Player.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::Vector2f player(0, 0);
	//Kevin
	Player p1 = Player();
	
	ShadowFactory shadowFactory;
	if (!shadowFactory.load())
		return -1;

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

		window.clear(sf::Color::White);
		for (auto s : shadowFactory.getShadows(player, sf::Color::Black))
			window.draw(s);
		window.draw(p1);
		window.display();
	}

	return 0;
}