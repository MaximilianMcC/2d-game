#pragma once

#include "mapObjects.h"

class Player : public DynamicMapObject
{
private:
	sf::RectangleShape body;
	
public:
	float Speed;

	Player(sf::Vector2f spawnPoint);

	void Update() override;
	void Draw() override;
	void CleanUp() override;

	void SolveCollision(sf::FloatRect& newHitbox, sf::Vector2f direction);
};