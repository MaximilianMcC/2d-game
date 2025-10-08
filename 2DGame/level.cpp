#include "level.h"
#include "assetManager.h"
#include "numericalVectors.h"
#include "player.h"

sf::Vector2f Level::TileSize = sf::Vector2f(16.f, 16.f);

//! this whole thing is temp debug
void Level::Load()
{
	// Load the textures
	AssetManager::LoadTexture("test", "C:/test.png");
	AssetManager::LoadTexture("bricks", "./assets/sprite/bricks.png");

	// Add some blocks
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(0, 0), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(1, 1), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(3, 2), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(3, 4), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(5, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(6, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(7, 5), true));
	MapObjects.push_back(new Tile("bricks", TileSize * sf::Vector2f(8, 5), true));
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

std::optional<sf::FloatRect> Level::GetCollision(MapObject &thing)
{
	// Loop over all map objects
	std::optional<sf::FloatRect> collision;
	for (int i = 0; i < MapObjects.size(); i++)
	{
		// Check for if we allow collision
		if (MapObjects[i]->HasCollision == false) continue;

		// We cannot collide with ourself
		if (MapObjects[i] == &thing) continue;

		// Get the actual collision
		collision = thing.Hitbox.findIntersection(MapObjects[i]->Hitbox);
		if (collision.has_value()) break;
	}

	// Give back the float rect thing
	return collision;
}