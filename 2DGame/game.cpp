#include "game.h"
#include "gameManager.h"
#include "forklift.h"

#include "map.h"

void Game::Start()
{
	map = new Map("./assets/level/debug.txt");
	mapTexture = sf::RectangleShape(static_cast<sf::Vector2f>(map->GetMapTexture()->getSize()));
	mapTexture.setTexture(map->GetMapTexture());
}

void Game::Draw()
{
	Utils::GetWindow()->draw(mapTexture);
}

void Game::CleanUp()
{
	delete map;
	map = nullptr;
}