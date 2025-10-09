#include <SFML/Graphics.hpp>
#include "utils.h"
#include "logger.h"
#include "level.h"
#include "player.h"

Level level;
Player* player;

void Start()
{
	player = new Player(sf::Vector2f(0.f, 0.f));

	level = Level();
	level.Load("./assets/level/debug.txt", player);
}

void Update()
{
	player->Update();
	level.Update();
}

void Draw()
{
	level.Draw();
	player->Draw();
}

void CleanUp()
{
	level.Unload();

	delete player;
	player = nullptr;
}

int main()
{
	Logger::SetLogLevel(Logger::LogLevel::EVERYTHING);

	// Make the SFML window
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Tactical restart");

	// Delta time setup
	float deltaTime = 0.0f;
	sf::Clock deltaTimeClock = sf::Clock();

	// Share common stuff
	Utils::Init(&window, &deltaTime);

	Start();

	while (window.isOpen())
	{
		// Calculate delta time
		deltaTime = deltaTimeClock.restart().asSeconds();

		// Check for any events
		while (const std::optional event = window.pollEvent())
		{
			// Check for if we wanna close the window
			if (event->is<sf::Event::Closed>()) window.close();
		}

		Update();

		window.clear(sf::Color::Magenta);
		Draw();
		window.display();
	}

	CleanUp();
}