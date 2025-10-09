#pragma once

#include "mapObjects.h"

class Lever : public DynamicMapObject
{
private:
	sf::RectangleShape shape;

public:
	bool Flipped = false;

	Lever(sf::Vector2f position, bool flipped = false);

	void Draw() override;
	void Flip();
};