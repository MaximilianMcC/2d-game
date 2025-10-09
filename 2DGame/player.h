#pragma once

#include "mapObjects.h"
#include "collisionHandler.h"

class Player : public DynamicMapObject
{
private:
	sf::RectangleShape body;
	bool onTheGroundRn = false;
	float yVelocity = 0.0f;
	bool previouslyInteracted;

	CollisionHandler::CollisionInfo Move();
	bool JustInteracted();

public:
	float Speed;
	float JumpForce;

	Player(sf::Vector2f spawnPoint);

	void Update() override;
	void Draw() override;
	void CleanUp() override;
};