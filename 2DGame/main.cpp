#include <SFML/Graphics.hpp>
#include "gameManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "SFML works!");

	GameManager::StartEverything();

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