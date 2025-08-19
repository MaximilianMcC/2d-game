#include "mainMenu.h"
#include <iostream>
#include "gameManager.h"
#include "game.h"

void MainMenu::Start()
{
	std::cout << "main menu" << std::endl;
}

void MainMenu::Update()
{
	std::cout << "updates" << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		std::cout << "keyboarcd" << std::endl;
		GameManager::SetScene(new Game());
	}
}

void MainMenu::CleanUp()
{
	std::cout << "main menu dead" << std::endl;
}