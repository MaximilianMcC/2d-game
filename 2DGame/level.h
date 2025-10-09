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
	static int Width;
	static int Height;

	void Load(std::string mapFilePath);
	void Update();
	void Draw();
	void Unload();
};