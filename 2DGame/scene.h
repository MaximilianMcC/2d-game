#pragma once

#include <SFML/Graphics.hpp>

class Scene
{
public:
	virtual void Start() { }
	virtual void Update() { }
	virtual void Draw() { }
	virtual void CleanUp() { }
};