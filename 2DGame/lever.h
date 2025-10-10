#pragma once

#include "mapObjects.h"

class Lever : public DynamicMapObject
{
public:
	bool Flipped = false;

	Lever(sf::Vector2f position, bool flipped = false);

	void Flip();
};