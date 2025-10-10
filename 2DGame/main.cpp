#include <SFML/Graphics.hpp>
#include "utils.h"
#include "logger.h"
#include "level.h"
#include "player.h"

Level level;
Player player;

void Start()
{
	// TODO: Just put the player in the level because this is confusing and slow as
	player = Player();

	level = Level();
	level.Load("./assets/level/debug.txt", player);
}

void Update()
{
	player.Update();
	level.Update();
}

void Draw()
{
	level.Draw();
	player.Draw();
}

void CleanUp()
{
	level.Unload();
}

int main()
{
	Logger::SetLogLevel(Logger::LogLevel::EVERYTHING);

	// Make the SFML window
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "top 10 nonchalant html elements");

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