#pragma once

#include "mapObjects.h"

class Door : public DynamicMapObject
{
public:
	bool Opened = false;

	Door(sf::Vector2f position);

	void Open();
	void Close();
};