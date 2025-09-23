#pragma once

#include <vector>
#include <map>
#include "gameObject.h"
#include "scene.h"
#include "logger.h"

class GameManager
{
private:
	static std::vector<GameObject*> gameObjects;

	static Scene* activeScene;
	static bool changingScene;

public:
	static void UpdateEverything();
	static void DrawEverything();
	static void CleanUpEverything();

	static void SetScene(Scene* newScene);

	static void Add(GameObject* gameObjectToAdd, std::string name = "idk");
	static GameObject* GetFromName(std::string name);
};