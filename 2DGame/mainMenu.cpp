#include "mainMenu.h"
#include <iostream>
#include "gameManager.h"
#include "game.h"

void MainMenu::Start()
{
	std::cout << "kia ora please make a main menu ok thanks ka pai" << std::endl;
	GameManager::SetScene(new Game());

}