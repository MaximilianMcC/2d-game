#pragma once

#include "gameObject.h"

class Forklift : public GameObject
{
private:
	sf::Sprite* forklift;
	sf::Sprite* fork;
	sf::Sprite* wheelLeft;
	sf::Sprite* wheelRight;

	sf::Vector2f wheelLeftPosition;
	sf::Vector2f wheelRightPosition;

	sf::Vector2f position;
	float driveSpeed = 120.f;

	// TODO: Make const
	sf::Vector2f forkOriginOffset;
	float liftHeight;
	float forkPosition;
	float forkSpeed = 100.f;

public:
	void Start() override;
	void Update() override;
	void Draw() override;
	void CleanUp() override;

	void MoveFork();
	void Drive();
};