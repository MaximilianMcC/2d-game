#pragma once

#include <SFML/Graphics.hpp>
#include "map.h"

class CollisionHandler
{
public:

	// TODO: Return overlap
	bool WasCollisionWithMap(sf::FloatRect thing, Map& map);
};