#pragma once

#include "scene.h"

class Game : public Scene
{
public:
	void Start() override;
	void Draw() override;
	void CleanUp() override;

private:
	Map* map;
	sf::RectangleShape mapTexture;
};