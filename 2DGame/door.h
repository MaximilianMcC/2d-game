#pragma once

#include "mapObjects.h"

class Door : public DynamicMapObject
{
private:
	sf::RectangleShape shape;

public:
	bool Opened = false;

	Door(sf::Vector2f position);
	void Draw() override;

	void Open();
	void Close();
};