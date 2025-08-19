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
	float accelerationCoefficient = 5.f;
	float friction = 65.f;
	float maxSpeed = 350.f;

public:
	void Start() override;
	void Update() override;
	void Draw() override;

	int GetDirection() { return (int)(velocity.x / abs(velocity.x)); }
};