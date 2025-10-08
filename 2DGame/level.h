#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "mapObjects.h"
#include "utils.h"

class Level
{
public:
	static sf::Vector2f TileSize;
	static float Gravity;
	static std::vector<MapObject*> MapObjects;

	void Load();
	void Draw();
	void Unload();
};