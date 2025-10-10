#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "assetManager.h"

class Debugger
{
private:
	struct Variable
	{
		float* Pointer;
		sf::Text Label;
		std::string Name;
		sf::Keyboard::Key IncreimentKey;
		sf::Keyboard::Key DecreimentKey;
		float adjustAmount;
	};

	static std::vector<Variable> variables;

public:
	static sf::RenderWindow Window;

	static void InitWindow();
	static void RegisterVariable(float* variablePointer, std::string variableName, sf::Keyboard::Key increimentKey, sf::Keyboard::Key decreimentKey, float adjustAmount = 1.0f);

	static void Update();
	static void Draw();
};