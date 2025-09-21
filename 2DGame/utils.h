#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

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

	static std::vector<std::string> Split(std::string string, std::string delimiter);
	static bool StringEndsWith(std::string string, std::string ending);

	static sf::Vector2f IndexToCoordinates(int index, int width);
	static int CoordinatesToIndex(sf::Vector2f coordinates, int width);
};