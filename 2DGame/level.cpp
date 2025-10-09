#include "level.h"
#include <iostream>
#include <fstream>
#include <string>
#include "assetManager.h"
#include "numericalVectors.h"
#include "player.h"
#include "crackedBricks.h"
#include "lava.h"
#include "lever.h"

sf::Vector2f Level::TileSize = sf::Vector2f(16.f, 16.f) * 1.5f;
float Level::Gravity = 350.f;
std::vector<MapObject*> Level::MapObjects;
int Level::Width = 0;
int Level::Height = 0;

// TODO: Do not pass player in like this
void Level::Load(std::string mapFilePath, Player* player)
{
	// Load the textures
	AssetManager::LoadTexture("bricks", "./assets/sprite/bricks.png");

	// Open the file
	std::ifstream mapFile(mapFilePath);
	if (mapFile.is_open() == false)
	{
		std::cerr << "issue opening map file at \"" << mapFilePath << "\"" << std::endl;
		return;
	}

	// Reset everything from the previous level
	MapObjects.clear();
	Width = 0;
	Height = 0;

	// Loop over every line in the file
	std::string line;
	sf::Vector2f currentCoordinates = sf::Vector2f(0.0f, 0.0f);
	while (std::getline(mapFile, line))
	{
		// Every character is a tile
		std::vector<std::string> tiles = Utils::Split(line, "");
		for (size_t i = 0; i < tiles.size(); i++)
		{
			// Get the coordinates of the current tile
			sf::Vector2f tileCoordinates = TileSize * currentCoordinates;

			// Check for what kinda tile we're making
			// TODO: Use switch		
			if (tiles[i] == "w")
			{
				// Normal wall
				MapObjects.push_back(new Tile("bricks", tileCoordinates, true));
			}
			else if (tiles[i] == "l")
			{
				// Lava
				MapObjects.push_back(new Lava(tileCoordinates));
			}
			else if (tiles[i] == "c")
			{
				// Cracked bricks
				MapObjects.push_back(new CrackedBricks(tileCoordinates));
			}
			else if (tiles[i] == "k")
			{
				// Lever
				//? is a k because it looks like both states of it yk
				MapObjects.push_back(new Lever(tileCoordinates, false));
			}
			else if (tiles[i] == "p")
			{
				// Player
				player->Hitbox.position = tileCoordinates;
			}

			// Update the coordinates for the next tile
			currentCoordinates.x++;

			// Update the max width
			if (Width + 1 > Width) Width++;
		}

		// Update the max height and reset the
		// coordinates x position for the new line
		Height++;
		currentCoordinates.x = 0.0f;
		currentCoordinates.y++;
	}

	// Done
	mapFile.close();	
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