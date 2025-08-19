#pragma once

#include "gameObject.h"
#include <iostream>

class Player : public GameObject
{
public:
	void Start() override;
	void Update() override;
	void Draw() override;
};