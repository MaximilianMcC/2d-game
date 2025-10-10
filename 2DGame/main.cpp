#include <SFML/Graphics.hpp>
#include "utils.h"
#include "logger.h"
#include "level.h"
#include "player.h"
#include "debugger.h"
#include "crackedBricks.h"

Level level;
Player player;

void Start()
{
	// TODO: Just put the player in the level because this is confusing and slow as
	player = Player();

	level = Level();
	level.Load("./assets/level/debug.txt", player);

	// TODO: Do this in the player
	Debugger::RegisterVariable(
		&player.Speed, "Player speed",
		sf::Keyboard::Key::P,
		sf::Keyboard::Key::O
	);

	// TODO: Do this in the brick
	Debugger::RegisterVariable(
		&CrackedBricks::TimeBeforeBrickFalls, "time before brick falls",
		sf::Keyboard::Key::L,
		sf::Keyboard::Key::K,
		0.01f
	);
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
	
	// Make the SFML windows
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "top 10 nonchalant html elements");

	// Delta time setup
	float deltaTime = 0.0f;
	sf::Clock deltaTimeClock = sf::Clock();

	// Share common stuff
	Utils::Init(&window, &deltaTime);

	Start();

	sf::Color backgroundColor = sf::Color(0x333333ff);

	// Game window
	while (window.isOpen() || Debugger::Window.isOpen())
	{
		// Calculate delta time
		deltaTime = deltaTimeClock.restart().asSeconds();

		// Check for any events on the main window
		while (const std::optional event = window.pollEvent())
		{
			// Check for if we wanna close the window
			if (event->is<sf::Event::Closed>()) window.close();
		}

		// Check for any events on the debug menu
		while (const std::optional event = Debugger::Window.pollEvent())
		{
			// Check for if we wanna close the window
			if (event->is<sf::Event::Closed>()) Debugger::Window.close();
		}

		Debugger::Update();
		Update();

		Debugger::Window.clear(sf::Color::White);
		Debugger::Draw();
		Debugger::Window.display();

		window.clear(backgroundColor);
		Draw();
		window.display();
	}

	CleanUp();
}