#include "game.h"
#include "gameManager.h"
#include "forklift.h"

#include "map.h"

void Game::Start()
{
	Map* map = new Map("./assets/level/debug.txt");
	
	GameManager::Add(new Forklift(), "Forklift");
}

void Game::CleanUp()
{
	
}