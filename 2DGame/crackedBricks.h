#pragma once

#include "mapObjects.h"

class CrackedBricks : public DynamicMapObject
{
private:
	float yVelocity = 0.f;
	sf::Vector2f initialPosition;

	bool beenSteppedOn = false;
	bool cracked = false;
	float timer = 0.f;
public:

	// Settings
	static float TimeBeforeBrickFalls;
	static float TimeBeforeBrickRespawns;

	CrackedBricks(sf::Vector2f position);
	void Update() override;

	void Crack();
};