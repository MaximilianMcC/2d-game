#include "game.h"
#include "gameManager.h"
#include "player.h"

void Game::Start()
{
    // Make the player
    GameManager::Add(new Player(), "Player");
}

void Game::CleanUp()
{
    
}