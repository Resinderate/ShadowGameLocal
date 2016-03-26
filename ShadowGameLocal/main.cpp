#include "SFML/Graphics.hpp"
#include "VectorAlgebra2D.hpp"
#include "ShadowFactory.hpp"
#include "Player.hpp"
#include "Attributes.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::Vector2f player(0, 0);
	//Kevin
	Player p1 = Player();
	Player p2 = Player("Kevin", "pass", sf::Vector2f(20,20), sf::Vector2f(0.078125, 0.078125), 2);
	
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
		for (auto s : shadowFactory.getShadows(p1.getPosition(), sf::Color::Black))
			window.draw(s);

		p1.Update(shadowFactory);
		p2.Update(shadowFactory);

		window.draw(p1);
		window.draw(p2);

		window.display();
	}

	return 0;
}