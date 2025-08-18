#pragma once

#include <vector>
#include "gameObject.h"

class GameManager
{
private:
	static std::vector<GameObject*> gameObjects;

public:
	static void StartEverything();
	static void UpdateEverything();
	static void DrawEverything();
	static void CleanUpEverything();
};