#include "SFML/Graphics.hpp"
#include "VectorAlgebra2D.hpp"
#include "ShadowFactory.hpp"
#include "Player.hpp"
#include "PlayerDatabase.hpp"
#include "Attributes.hpp"
#include "TexturedWorld.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1260, 700), "SFML works!");
	// P1 view.
	sf::View p1View(sf::FloatRect(0, 0, 600, 600));
	p1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	// P2 view.
	sf::View p2View(sf::FloatRect(0, 0, 600, 600));
	p2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));

	sf::Clock timer;
	// Time in seconds.
	float deltaTime;

	sf::Texture t;
	t.loadFromFile("spritesheet/hitman_walk.png");
	Animation a;
	a.setSpriteSheet(t);
	a.addFrame(sf::IntRect(0, 0, 35, 43));
	a.addFrame(sf::IntRect(35, 0, 35, 43));
	std::vector<Animation> animations;
	animations.push_back(a);

	//Kevin
	Player p1 = Player("Kevin", "pass", sf::Vector2f(25, 25), 1, animations);
	Player p2 = Player("Ronan", "pass", sf::Vector2f(150, 25), 2, animations);
	PlayerDatabase players = PlayerDatabase();
	players.AddPlayer(p1);
	players.AddPlayer(p2);
	
	
	ShadowFactory shadowFactory;
	if (!shadowFactory.load())
		return -1;

	TexturedWorld texturedWorld;
	if (!texturedWorld.load())
		return -2;

	sf::Sprite hud;
	sf::Texture hudT;
	if (!hudT.loadFromFile("spritesheet/HUD.png"))
		return -2;

	hud.setTexture(hudT);

	
	timer.restart();
	while (window.isOpen())
	{
		// Input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update
		deltaTime = timer.restart().asSeconds();
		p1.Update(shadowFactory, deltaTime, players.GetPlayers());
		p2.Update(shadowFactory, deltaTime, players.GetPlayers());

		float rate = 50;
		sf::Vector2f p1Cen = p1View.getCenter() + ((p1.getPosition() - p1View.getCenter()) * rate * deltaTime);
		sf::Vector2f p2Cen = p2View.getCenter() + ((p2.getPosition() - p2View.getCenter()) * rate * deltaTime);
		p1View.setCenter(p1Cen);
		p2View.setCenter(p2Cen);

		window.clear(sf::Color::White);

		// Draw P1
		window.setView(p1View);

		// Draw background
		for (auto spr : texturedWorld.getTexturedWorld())
			window.draw(spr);

		window.draw(p1);
		window.draw(p2);

		// Draw shadows
		sf::Vector2f castingPos = sf::Vector2f(p1.getPosition().x + p1.getGlobalBounds().width / 2, p1.getPosition().y + p1.getGlobalBounds().height / 2);
		for (auto sha : shadowFactory.getShadows(castingPos, sf::Color::Black))
			window.draw(sha);

		// Draw P2
		window.setView(p2View);
		
		// Draw background
		for (auto spr : texturedWorld.getTexturedWorld())
			window.draw(spr);

		window.draw(p1);
		window.draw(p2);

		// Draw shadows
		castingPos = sf::Vector2f(p2.getPosition().x + p2.getGlobalBounds().width / 2, p2.getPosition().y + p2.getGlobalBounds().height / 2);
		for (auto sha : shadowFactory.getShadows(castingPos, sf::Color::Black))
			window.draw(sha);
		
		// Draw hud
		window.setView(window.getDefaultView());
		window.draw(hud);
		
		window.display();
	}

	return 0;
}