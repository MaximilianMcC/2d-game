#include <SFML/Graphics.hpp>
#include "gameManager.h"

#include "player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "john ");

	GameManager::Add(new Player(), "player");

	while (window.isOpen())
	{
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