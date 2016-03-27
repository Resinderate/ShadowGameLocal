#include "SFML/Graphics.hpp"
#include "VectorAlgebra2D.hpp"
#include "ShadowFactory.hpp"
#include "Player.hpp"
#include "Attributes.hpp"
#include "TexturedWorld.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::View p1View(sf::FloatRect(0, 0, 800, 600));
	window.setView(p1View);

	//Kevin
	Player p1 = Player("Kevin", "pass", sf::Vector2f(100, 100), sf::Vector2f(0.078125, 0.078125), 1);
	
	ShadowFactory shadowFactory;
	if (!shadowFactory.load())
		return -1;

	TexturedWorld texturedWorld;
	if (!texturedWorld.load())
		return -2;

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
		p1View.setCenter(p1.getPosition());
		window.setView(p1View);

		// Draw
		window.clear(sf::Color::White);
		// Draw background
		for (auto spr : texturedWorld.getTexturedWorld())
			window.draw(spr);

		// Draw shadows
		sf::Vector2f castingPos = sf::Vector2f(p1.getPosition().x + p1.getGlobalBounds().width / 2, p1.getPosition().y + p1.getGlobalBounds().height / 2);
		for (auto sha : shadowFactory.getShadows(castingPos, sf::Color::Black))
			window.draw(sha);
		window.draw(p1);
		window.display();
	}

	return 0;
}