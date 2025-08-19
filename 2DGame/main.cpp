#include <SFML/Graphics.hpp>
#include "gameManager.h"

#include "player.h"
#include "utils.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "john ");

	// Delta time setup
	float deltaTime = 0.0f;
	sf::Clock deltaTimeClock = sf::Clock();

	// Share common stuff
	Utils::Init(&window, &deltaTime);

	// TODO: Do in a scene class or whatever
	GameManager::Add(new Player(), "player");

	while (window.isOpen())
	{
		// Calculate delta time and fps
		//? Since a pointer was given we don't need to bother updating it
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