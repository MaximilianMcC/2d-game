#include "level.h"
#include "assetManager.h"
#include "numericalVectors.h"
#include "player.h"
#include "crackedBricks.h"

// sf::Vector2f Level::TileSize = sf::Vector2f(16.f, 16.f);
sf::Vector2f Level::TileSize = sf::Vector2f(16.f, 16.f) * 1.5f;
float Level::Gravity = 350.f;
std::vector<MapObject*> Level::MapObjects;

//! this whole thing is temp debug
void Level::Load()
{
	// Load the textures
	AssetManager::LoadTexture("test", "C:/test.png");
	AssetManager::LoadTexture("bricks", "./assets/sprite/bricks.png");

	// Add some blocks
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(1, 1), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(3, 2), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(3, 4), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(5, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(6, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(7, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(8, 5), true));

	MapObjects.push_back(new CrackedBricks(TileSize * sf::Vector2f(20, 15)));
	MapObjects.push_back(new CrackedBricks(TileSize * sf::Vector2f(21, 15)));
	MapObjects.push_back(new CrackedBricks(TileSize * sf::Vector2f(22, 15)));
	MapObjects.push_back(new CrackedBricks(TileSize * sf::Vector2f(23, 15)));

	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(24, 15), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(25, 15), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(26, 15), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(27, 15), true));

	// Add some more blocks
	for (int i = 0; i < 15; i++)
	{
		MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(5 + i, 15), true));
		MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(5 + i, 16), true));
	}
	
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