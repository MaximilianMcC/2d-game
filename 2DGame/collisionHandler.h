#pragma once

#include <SFML/Graphics.hpp>
#include "mapObjects.h"

class CollisionHandler
{
public:

	struct CollisionInfo
	{
		bool Left;
		bool Right;
		bool Top;
		bool Bottom;

		//? there might be two (one for x, one for y)
		// TODO: Add all
		MapObject* Victim;
	};

	static CollisionInfo SolveCollisionWithWorld(sf::FloatRect &hitbox, sf::FloatRect &newHitbox, sf::Vector2f direction);
};