#include "gameManager.h"

std::vector<GameObject*> GameManager::gameObjects;

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



GameObject* GameManager::GetFromName(std::string name)
{
	// Loop over all game obejcts
	for (GameObject* object : gameObjects)
	{
		// Check for if its name matches
		// the one we're looking for
		if (object->GetName() == name) return object;
	}

	// We didn't find the object. Return a null pointer
	return nullptr;
}

void GameManager::Add(GameObject* gameObjectToAdd, std::string name)
{
	// Chuck the game object into the list
	gameObjects.push_back(gameObjectToAdd);

	// Set the name of the game object
	gameObjectToAdd->SetName(name);

	// Start it
	gameObjectToAdd->Start();
}