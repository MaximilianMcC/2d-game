#pragma once

#include "mapObjects.h"

class Player : public DynamicMapObject
{
private:
	sf::RectangleShape body;
	bool onTheGroundRn = false;
	float yVelocity = 0.0f;
	
	struct CollisionInfo
	{
		bool Left;
		bool Right;
		bool Top;
		bool Bottom;

		//? there might be two (one for x, one for y)
		MapObject* Victim;
	};

public:
	float Speed;
	float JumpForce;

	Player(sf::Vector2f spawnPoint);

	void Update() override;
	void Draw() override;
	void CleanUp() override;

	CollisionInfo SolveCollision(sf::FloatRect& newHitbox, sf::Vector2f direction);
	CollisionInfo Move();
};