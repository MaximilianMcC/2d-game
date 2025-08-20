#include "game.h"
#include "gameManager.h"
#include "forklift.h"

void Game::Start()
{
	GameManager::Add(new Forklift(), "Forklift");
}

void Game::CleanUp()
{
	
}