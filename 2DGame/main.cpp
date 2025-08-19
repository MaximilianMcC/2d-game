#include <SFML/Graphics.hpp>
#include "gameManager.h"

#include "utils.h"
#include "mainMenu.h"

int main()
{
	// Make the SFML window
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "john idk");

	// Delta time setup
	float deltaTime = 0.0f;
	sf::Clock deltaTimeClock = sf::Clock();

	// Share common stuff
	Utils::Init(&window, &deltaTime);

	// Set the initial scene/entry point
	GameManager::SetScene(new MainMenu());

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

		GameManager::UpdateEverything();

		window.clear();
		GameManager::DrawEverything();
		window.display();
	}

	GameManager::CleanUpEverything();
}