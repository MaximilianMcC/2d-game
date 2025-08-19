#pragma once

#include <SFML/Graphics.hpp>

class Utils
{
private:
	static sf::RenderWindow* window;
	static float* deltaTime;

public:
	static void Init(sf::RenderWindow* mainWindow, float* deltaTimePointer)
	{
		window = mainWindow;
		deltaTime = deltaTimePointer;
	}

	static sf::RenderWindow* GetWindow() { return window; }
	static float GetDeltaTime() { return *deltaTime; }
};