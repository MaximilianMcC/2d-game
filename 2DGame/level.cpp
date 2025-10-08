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
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(0, 10), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(1, 10), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(2, 10), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(3, 10), true));

	// MapObjects.push_back(new CrackedBricks(TileSize * sf::Vector2f(5, 10)));
	MapObjects.push_back(new CrackedBricks(TileSize * sf::Vector2f(6, 10)));
	// MapObjects.push_back(new CrackedBricks(TileSize * sf::Vector2f(7, 10)));

	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(9, 10), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(10, 10), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(11, 10), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(12, 10), true));
	
}

void Level::Update()
{
	// Loop over all dynamic objects and update them
	// TODO: Put dynamic objects in a seperate list
	DynamicMapObject* updatableObject = nullptr;
	for (size_t i = 0; i < MapObjects.size(); i++)
	{
		updatableObject = dynamic_cast<DynamicMapObject*>(MapObjects[i]);
		if (updatableObject) updatableObject->Update();
	}
}

// TODO: Take in a camera/view param
void Level::Draw()
{
	for (size_t i = 0; i < MapObjects.size(); i++)
	{
		MapObjects[i]->Draw();
	}
}

void Level::Unload()
{
	// Remove all the map objects
	for (size_t i = 0; i < MapObjects.size(); i++)
	{
		delete MapObjects[i];
		MapObjects[i] = nullptr;
	}
	MapObjects.clear();
}