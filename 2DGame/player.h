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
	sf::Vector2f spawnPoint;

	CollisionHandler::CollisionInfo Move();
	bool JustInteracted();

public:
	float Speed;
	float JumpForce;
	bool Dead = false;

	Player(sf::Vector2f spawnPoint);

	void Update() override;
	void Draw() override;
	void CleanUp() override;

	void SetSpawnpoint(sf::Vector2f coordinates);
	void Die();
};