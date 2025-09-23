#include "mainMenu.h"
#include <iostream>
#include "gameManager.h"
#include "game.h"

void MainMenu::Start()
{
	Logger::Log("kia ora please make a main menu ok thanks ka pai", Logger::TODO);
	GameManager::SetScene(new Game());
}