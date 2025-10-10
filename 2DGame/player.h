#pragma once

#include "mapObjects.h"
#include "collisionHandler.h"
#include "dropDownPlatform.h"

class Player : public DynamicMapObject
{
private:
	bool onTheGroundRn = false;
	float yVelocity = 0.0f;
	bool previouslyInteracted = false;
	sf::Vector2f spawnPoint;

	CollisionHandler::CollisionInfo Move();
	bool JustInteracted();

public:
	float Speed;
	float JumpForce;
	bool Dead = false;

	Player();

	void Update() override;

	void SetSpawnpoint(sf::Vector2f coordinates);
	void Die();
};