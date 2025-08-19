#pragma once

#include <vector>
#include <map>
#include "gameObject.h"

class GameManager
{
private:
	static std::vector<GameObject*> gameObjects;

public:
	static void UpdateEverything();
	static void DrawEverything();
	static void CleanUpEverything();

	static void Add(GameObject* gameObjectToAdd, std::string name = "idk");
	static GameObject* GetFromName(std::string name);
};