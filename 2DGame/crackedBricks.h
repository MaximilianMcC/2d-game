#pragma once

#include "mapObjects.h"

class CrackedBricks : public DynamicMapObject
{
private:
	sf::RectangleShape shape;
	float yVelocity = 0.f;
	sf::Vector2f initialPosition;

	bool beenSteppedOn = false;
	bool cracked = false;
	float timer = 0.f;

	// Settings
	float timeBeforeBrickFalls = 2.f;
	float timeBeforeBrickRespawns = 3.f;

public:
	CrackedBricks(sf::Vector2f position);
	void Update() override;
	void Draw() override;

	void Crack();
};