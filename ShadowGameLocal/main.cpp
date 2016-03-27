#include "SFML/Graphics.hpp"
#include "VectorAlgebra2D.hpp"
#include "ShadowFactory.hpp"
#include "Player.hpp"
#include "Attributes.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	//Kevin
	Player p1 = Player("Kevin", "pass", sf::Vector2f(100, 100), sf::Vector2f(0.078125, 0.078125), 1);
	
	ShadowFactory shadowFactory;
	if (!shadowFactory.load())
		return -1;

	while (window.isOpen())
	{
		// Input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// pdate
		p1.Update(shadowFactory);

		// Draw
		window.clear(sf::Color::White);
		for (auto s : shadowFactory.getShadows(sf::Vector2f(p1.getPosition().x + p1.getGlobalBounds().width / 2,
															p1.getPosition().y + p1.getGlobalBounds().height / 2), 
															sf::Color::Black))
			window.draw(s);
		window.draw(p1);
		window.display();
	}

	return 0;
}