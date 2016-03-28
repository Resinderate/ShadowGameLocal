#include "SFML/Graphics.hpp"
#include "VectorAlgebra2D.hpp"
#include "ShadowFactory.hpp"
#include "Player.hpp"
#include "PlayerDatabase.hpp"
#include "Attributes.hpp"
#include "TexturedWorld.hpp"
#include <iostream>
#include "SFML/Audio.hpp"

sf::Music music;
sf::Sprite hud;
sf::Texture hudT;
PlayerDatabase players;
Player p1;
Player p2;

ShadowFactory shadowFactory;
TexturedWorld texturedWorld;

sf::Vector2f p1Cen;
sf::Vector2f p2Cen;
sf::View p1View(sf::FloatRect(0, 0, 600, 600));
sf::View p2View(sf::FloatRect(0, 0, 600, 600));

sf::Clock timer;
// Time in seconds.
float deltaTime;

sf::Texture t;
Animation a;
std::vector<Animation> animations;

void Update();
void Draw();
void Load();
void LoadMusic();
void LoadTextures();
void LoadViewports();
void LoadAnimation();
void LoadWorld();
void LoadPlayers();


sf::RenderWindow window(sf::VideoMode(1260, 700), "SFML works!");

int main()
{
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
		Update();
		Draw();
	}
	return 0;
}

void Update()
{
	deltaTime = timer.restart().asSeconds();
	players.GetPlayers()[0].Update(shadowFactory, deltaTime, players.GetPlayers());
	players.GetPlayers()[1].Update(shadowFactory, deltaTime, players.GetPlayers());

	float rate = 50;
	p1Cen = p1View.getCenter() + ((players.GetPlayers()[0].getPosition() - p1View.getCenter()) * rate * deltaTime);
	p2Cen = p2View.getCenter() + ((players.GetPlayers()[1].getPosition() - p2View.getCenter()) * rate * deltaTime);
	p1View.setCenter(p1Cen);
	p2View.setCenter(p2Cen);

}
void Draw()
{
	window.clear(sf::Color::White);

	// Draw P1
	window.setView(p1View);

	// Draw background
	for (auto spr : texturedWorld.getTexturedWorld())
		window.draw(spr);

	if (!players.GetPlayers()[0].GetIsDead())
		window.draw(players.GetPlayers()[0]);
	if (!players.GetPlayers()[1].GetIsDead())
		window.draw(players.GetPlayers()[1]);

	// Draw shadows
	sf::Vector2f castingPos = sf::Vector2f(players.GetPlayers()[0].getPosition().x + players.GetPlayers()[0].getGlobalBounds().width / 2, players.GetPlayers()[0].getPosition().y + players.GetPlayers()[0].getGlobalBounds().height / 2);
	for (auto sha : shadowFactory.getShadows(castingPos, sf::Color::Black))
		window.draw(sha);

	// Draw P2
	window.setView(p2View);

	// Draw background
	for (auto spr : texturedWorld.getTexturedWorld())
		window.draw(spr);

	if (!players.GetPlayers()[0].GetIsDead())
		window.draw(players.GetPlayers()[0]);
	if (!players.GetPlayers()[1].GetIsDead())
		window.draw(players.GetPlayers()[1]);

	// Draw shadows
	castingPos = sf::Vector2f(players.GetPlayers()[1].getPosition().x + players.GetPlayers()[1].getGlobalBounds().width / 2, players.GetPlayers()[1].getPosition().y + players.GetPlayers()[1].getGlobalBounds().height / 2);
	for (auto sha : shadowFactory.getShadows(castingPos, sf::Color::Black))
		window.draw(sha);

	// Draw hud
	window.setView(window.getDefaultView());
	window.draw(hud);

	window.display();
}
void Load()
{
	LoadMusic();
	LoadTextures();
	LoadWorld();
	LoadAnimation();
	LoadViewports();
	LoadPlayers();
}

void LoadMusic()
{
	if (!music.openFromFile("audio/background.wav"))
		return; 

	music.setLoop(true);
	music.setVolume(50);
	music.play();
}
void LoadTextures()
{
	if (!texturedWorld.load())
		return;

	if (!hudT.loadFromFile("spritesheet/HUD.png"))
		return;

	hud.setTexture(hudT);
}
void LoadViewports()
{
	// P1 view.
	p1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	// P2 view.
	p2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
}
void LoadAnimation()
{
	t.loadFromFile("spritesheet/hitman_walk.png");
	a.setSpriteSheet(t);
	a.addFrame(sf::IntRect(0, 0, 35, 43));
	a.addFrame(sf::IntRect(35, 0, 35, 43));
	animations.push_back(a);
}
void LoadWorld()
{
	if (!shadowFactory.load())
		return;
}
void LoadPlayers()
{
	//Kevin
	p1 = Player("Kevin", "pass", sf::Vector2f(125, 25), 1, animations);
	p2 = Player("Ronan", "pass", sf::Vector2f(150, 25), 2, animations);
	players = PlayerDatabase();
	players.AddPlayer(p1);
	players.AddPlayer(p2);
}