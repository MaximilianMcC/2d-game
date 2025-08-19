#pragma once

#include "gameObject.h"
#include <iostream>

class Player : public GameObject
{
private:
	sf::RectangleShape body;

public:
	void Start() override;
	void Update() override;
	void Draw() override;
};