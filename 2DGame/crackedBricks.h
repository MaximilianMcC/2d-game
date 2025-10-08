#pragma once

#include "mapObjects.h"

class CrackedBricks : public DynamicMapObject
{
private:
	sf::RectangleShape shape;
public:
	CrackedBricks(sf::Vector2f position);
	void Draw() override;
};