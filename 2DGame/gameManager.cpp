#include "gameManager.h"

std::vector<GameObject*> GameManager::gameObjects;

void GameManager::StartEverything()
{
	// Loop over every single game object
	for (GameObject* object : gameObjects)
	{
		object->Start();
	}
}

void GameManager::UpdateEverything()
{
	// Loop over every single game object
	for (GameObject* object : gameObjects)
	{
		object->Update();
	}
}

void GameManager::DrawEverything()
{
	// Loop over every single game object
	for (GameObject* object : gameObjects)
	{
		object->Draw();
		object->DrawUi();
	}
}

void GameManager::CleanUpEverything()
{
	// Loop over every single game object
	for (GameObject* object : gameObjects)
	{
		object->CleanUp();

		// Remove the object from the list
		delete object;
		object = nullptr;
	}

	// Clear the list of objects
	// to fully erradicate them
	gameObjects.clear();
}
