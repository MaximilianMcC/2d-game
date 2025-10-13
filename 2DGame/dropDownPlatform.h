#pragma once

#include "mapObjects.h"

class DropDownPlatform : public DynamicMapObject
{
private:
	float dropDownTime = 1.0f;
	float timer = 0.0f;
	bool droppingDown = false;

public:
	DropDownPlatform(sf::Vector2f position);

	void Update() override;
	void Drop();
};