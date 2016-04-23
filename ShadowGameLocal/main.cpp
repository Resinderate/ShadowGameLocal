// Written by: Mixed

#include "SFML/Graphics.hpp"
#include "VectorAlgebra2D.hpp"
#include "ShadowFactory.hpp"
#include "Player.hpp"
#include "PlayerDatabase.hpp"
#include "Attributes.hpp"
#include "TexturedWorld.hpp"
#include <iostream>
#include "SFML/Audio.hpp"
#include "ItemDatabase.hpp"

//Music
sf::Music music;
//HUD
sf::Font font;
sf::Sprite hud;
sf::Texture hudT;
sf::Text score;
sf::Text health;

sf::Texture startTex;
sf::Sprite startSpr;
bool displayStart = true;

sf::Texture endTex;
sf::Sprite endSpr;
bool displayEnd = false;

sf::Text winner;

//Players
PlayerDatabase players;
Player p1;
ItemDatabase items;

ShadowFactory shadowFactory;
TexturedWorld texturedWorld;

//View
sf::Vector2f p1Cen;
sf::View p1View(sf::FloatRect(0, 0, 800, 600));

sf::Clock timer;
// Time in seconds.
float deltaTime;

sf::Texture hitT;
sf::Texture manT;
Animation hitAni1;
Animation hitAni2;
Animation manAni1;
Animation manAni2;
std::vector<Animation> animations1;
std::vector<Animation> animations2;

//Methods
void Update();
void Draw();
void Load();
void LoadMusic();
void LoadTextures();
void LoadViewports();
void LoadAnimation();
void LoadWorld();
void LoadPlayers();
void LoadHUD();

sf::RenderWindow window(sf::VideoMode(840, 700), "Shadow");

int main()
{
	Load();
	timer.restart();
	while (window.isOpen())
	{
		// Input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Return)
					displayStart = false;					
			}
		}
		// Update
		Update();
		Draw();
	}
	return 0;
}

void Update()
{
	if (!displayStart && !displayEnd)
	{
		deltaTime = timer.restart().asSeconds();
		players.Update(shadowFactory, deltaTime, items.GetItems());
		items.Update(shadowFactory, deltaTime);

		float rate = 0.1;
		p1Cen = p1View.getCenter() + ((players.GetPlayers()[0].getPosition() - p1View.getCenter()) * rate);
		p1View.setCenter(p1Cen);

		score.setString(players.GetPlayers()[0].GetUsername() + " Lives :\t\t" + std::to_string(players.GetPlayers()[0].GetScore()));
		health.setString(players.GetPlayers()[0].GetUsername() + " Health :\t  " + std::to_string(players.GetPlayers()[0].GetHealth()));

		// Check the end game.
		for (auto &p : players.GetPlayers())
		{
			if (p.GetScore() >= 3)
			{
				winner.setString("Winner: " + p.GetUsername());
				displayEnd = true;
			}
		}
	}
}

void Draw()
{
	window.clear(sf::Color::White);

	if (displayStart)
	{
		window.setView(window.getDefaultView());
		window.draw(startSpr);
		window.display();
	}
	else if (displayEnd)
	{
		window.setView(window.getDefaultView());
		window.draw(endSpr);
		window.draw(winner);
		window.display();
	}
	else
	{
		// Draw P1
		window.setView(p1View);

		// Draw background
		for (auto spr : texturedWorld.getTexturedWorld())
			window.draw(spr);

		if (!players.GetPlayers()[0].GetIsDead())
			window.draw(players.GetPlayers()[0]);

		//Draw Items
		for (auto itm : items.GetItems())
		{
			window.draw(itm);
		}

		// Draw shadows
		sf::Vector2f castingPos = sf::Vector2f(players.GetPlayers()[0].getPosition());
		for (auto sha : shadowFactory.getShadows(castingPos, sf::Color::Black))
			window.draw(sha);


		// Draw hud
		window.setView(window.getDefaultView());

		window.draw(hud);
		window.draw(score);
		window.draw(health);

		window.display();
	}
}
void Load()
{
	LoadMusic();
	LoadTextures();
	LoadHUD();
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
	music.setVolume(5);
	music.play();
}
void LoadTextures()
{
	if (!texturedWorld.load())
		return;

	startTex.loadFromFile("spritesheet/shadow.png");
	endTex.loadFromFile("spritesheet/over.png");

	startSpr.setTexture(startTex);
	endSpr.setTexture(endTex);
}
void LoadViewports()
{
	// P1 view.
	p1View.setViewport(sf::FloatRect(0, 0, 1, 1));

}
void LoadAnimation()
{
	hitT.loadFromFile("spritesheet/hitman_walk.png");
	hitAni1.setSpriteSheet(hitT);
	hitAni1.addFrame(sf::IntRect(0, 0, 35, 43));
	hitAni1.addFrame(sf::IntRect(35, 0, 35, 43));

	hitAni2.setSpriteSheet(hitT);
	hitAni2.addFrame(sf::IntRect(70, 0, 35, 43));

	animations1.push_back(hitAni1);
	animations1.push_back(hitAni2);

	manT.loadFromFile("spritesheet/man_walk.png");
	manAni1.setSpriteSheet(manT);
	manAni1.addFrame(sf::IntRect(0, 0, 35, 43));
	manAni1.addFrame(sf::IntRect(35, 0, 35, 43));

	manAni2.setSpriteSheet(manT);
	manAni2.addFrame(sf::IntRect(70, 0, 35, 43));

	animations2.push_back(manAni1);
	animations2.push_back(manAni2);
}
void LoadWorld()
{
	if (!shadowFactory.load())
		return;
	items = ItemDatabase();
}
void LoadPlayers()
{
	//Kevin
	p1 = Player("Player 1", "pass", sf::Vector2f(150, 50), 2, animations1);
	players = PlayerDatabase();
	players.AddPlayer(p1);
}

void LoadHUD()
{
	font.loadFromFile("font/Chunq.ttf");
	if (!hudT.loadFromFile("spritesheet/HUD.png"))
		return;
	hud.setTexture(hudT);

	SetupFont(score, font, sf::Color::Black, 20, 565, 18);
	SetupFont(health, font, sf::Color::Black, 20, 565, 38);
	SetupFont(winner, font, sf::Color::White, 20, 530, 450);

}

void SetupFont(sf::Text p_text, sf::Font p_font, sf::Color p_color, int p_size, float p_x, float p_y)
{
	p_text.setFont(p_font);
	p_text.setColor(p_color);
	p_text.setCharacterSize(p_size);
	p_text.setPosition(sf::Vector2f(p_x, p_y));
}