#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "mapObjects.h"
#include "utils.h"
#include "player.h"

class Level
{
public:
	static sf::Vector2f TileSize;
	static float Gravity;
	static std::vector<MapObject*> MapObjects;
	static int Width;
	static int Height;

	// TODO: Make static
	void Load(std::string mapFilePath, Player* player);
	void Update();
	void Draw();
	void Unload();
};