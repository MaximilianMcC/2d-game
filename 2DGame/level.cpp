#include "level.h"
#include "assetManager.h"
#include "numericalVectors.h"
#include "player.h"

sf::Vector2f Level::TileSize = sf::Vector2f(16.f, 16.f);
std::vector<MapObject*> Level::MapObjects;

//! this whole thing is temp debug
void Level::Load()
{
	// Load the textures
	AssetManager::LoadTexture("test", "C:/test.png");
	AssetManager::LoadTexture("bricks", "./assets/sprite/bricks.png");

	// Add some blocks
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(1, 0), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(1, 1), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(3, 2), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(3, 4), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(5, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(6, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(7, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(8, 5), true));

	// ↑ wall 
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(10, 10), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(10, 12), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(10, 13), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(10, 14), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(10, 15), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(10, 16), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(10, 17), true));
}

// TODO: Take in a camera/view param
void Level::Draw()
{
	for (int i = 0; i < MapObjects.size(); i++)
	{
		MapObjects[i]->Draw();
	}
}

void Level::Unload()
{
	// Remove all the map objects
	for (int i = 0; i < MapObjects.size(); i++)
	{
		delete MapObjects[i];
		MapObjects[i] = nullptr;
	}
	MapObjects.clear();
}