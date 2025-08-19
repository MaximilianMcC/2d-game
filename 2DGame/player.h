#pragma once

#include "gameObject.h"
#include <iostream>

class Player : public GameObject
{
private:
	sf::RectangleShape body;

	sf::Vector2f position;
	sf::Vector2f velocity;

	// TODO: Different friction values depending on floor surface
	float acceleration = 1300.f;
	float friction = 1200.f;
	float maxSpeed = 300.f;

public:
	void Start() override;
	void Update() override;
	void Draw() override;

	int GetDirection() { return velocity.x / abs(velocity.x); }
};