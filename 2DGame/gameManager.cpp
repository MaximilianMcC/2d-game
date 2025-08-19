#include "gameManager.h"

std::vector<GameObject*> GameManager::gameObjects;
Scene* GameManager::activeScene = nullptr;
bool GameManager::changingScene = false;

void GameManager::UpdateEverything()
{
	// The scene has now changed
	if (changingScene) changingScene = false;

	
	// Update every single thing
	activeScene->Update();
	for (GameObject* object : gameObjects)
	{
		object->Update();
	}
}

void GameManager::DrawEverything()
{
	// Do not draw if we're changing scene
	// since we'll be drawing the old scene
	// (we wanna wait for atleast one update to happen before drawing)
	if (changingScene) return;

	// Draw every single thing
	activeScene->Draw();
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
	// to fully eradicate them
	gameObjects.clear();

	// Finally get rid of the scene if
	// we already have one loaded
	if (activeScene != nullptr)
	{
		activeScene->CleanUp();
		delete activeScene;
		activeScene = nullptr;	
	}
}

void GameManager::SetScene(Scene* newScene)
{
	// Get rid of the old stuff
	changingScene = true;
	CleanUpEverything();

	// Replace it with the new scene
	activeScene = newScene;
	newScene->Start();
}

GameObject* GameManager::GetFromName(std::string name)
{
	// Loop over all game objects
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