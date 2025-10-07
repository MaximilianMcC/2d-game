#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "mapObjects.h"
#include "utils.h"

class Level
{
public:
	std::vector<MapObject> MapObjects;

	std::optional<sf::FloatRect> GetCollision(MapObject& thing);
};