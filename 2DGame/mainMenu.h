#pragma once

#include "scene.h"

class MainMenu : public Scene
{
public:
	void Start() override;
	void Update() override;
	// void Draw() override;
	void CleanUp() override;
};