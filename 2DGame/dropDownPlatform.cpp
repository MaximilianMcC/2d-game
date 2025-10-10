#include "dropDownPlatform.h"
#include "assetManager.h"
#include "level.h"

DropDownPlatform::DropDownPlatform(sf::Vector2f position)
{
	CreateDefaultHitbox(position, true);

	// Adjust the hitbox to be half
	// the height of a standard tile
	// to match the texture
	Hitbox.size.y /= 2;
	shape.setTexture(AssetManager::LoadAndGetTexture("drop-down-platform", "./assets/sprite/drop-down-platform.png"));
}

void DropDownPlatform::Update()
{
	if (droppingDown)
	{
		timer += Utils::GetDeltaTime();
		if (timer >= dropDownTime)
		{
			// Replace the collision when the
			// timer is over
			BlocksMovement = true;

			// Reset the timer
			timer = 0.0f;
		}
	}
}

void DropDownPlatform::Drop()
{
	droppingDown = true;
	BlocksMovement = false;
}