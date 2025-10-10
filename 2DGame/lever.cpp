#include "lever.h"
#include "level.h"
#include "assetManager.h"
#include "door.h"

Lever::Lever(sf::Vector2f position, bool flipped)
{
	CreateDefaultHitbox(position, false);

	// Load both textures
	// TODO: Don't do this every time
	AssetManager::LoadTexture("lever-up", "./assets/sprite/lever-up.png");
	AssetManager::LoadTexture("lever-down", "./assets/sprite/lever-down.png");

	// Set its properties
	BlocksMovement = false;
	Flipped = flipped;
	
	// Set the texture depending on if its flipped or not
	shape.setTexture(AssetManager::GetTexture(Flipped ? "lever-down" : "lever-up"));
}

void Lever::Flip()
{
	// Flip the lever
	Flipped = !Flipped;

	// Set the texture depending
	// on if its flipped or not
	// TODO: play a sound
	shape.setTexture(AssetManager::GetTexture(Flipped ? "lever-down" : "lever-up"));

	// The door being opened/closed is based
	// on if the lever is flicked or not
	// TODO: Don't hardcode this
	for (size_t i = 0; i < Level::MapObjects.size(); i++)
	{
		// Loop over every map object until we find the door
		Door* door = dynamic_cast<Door*>(Level::MapObjects[i]);
		if (door != nullptr)
		{
			// Check for if the door state
			// needs to be toggled
			if (Flipped) door->Open();
			else door->Close();
		}
	}

}
