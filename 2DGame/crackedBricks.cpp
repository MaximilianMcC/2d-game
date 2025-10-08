#include "crackedBricks.h"
#include "level.h"
#include "assetManager.h"
#include "utils.h"

CrackedBricks::CrackedBricks(sf::Vector2f position)
{
	// Make the hitbox and save the og
	// position so we can reset it when
	// the brick is respawned
	Hitbox = sf::FloatRect(position, Level::TileSize);
	initialPosition = position;

	// Load all the textures
	// TODO: Don't do this every time
	AssetManager::LoadTexture("cracked-bricks-0", "./assets/sprite/cracked-bricks-0.png");
	AssetManager::LoadTexture("cracked-bricks-1", "./assets/sprite/cracked-bricks-1.png");
	AssetManager::LoadTexture("cracked-bricks-2", "./assets/sprite/cracked-bricks-2.png");
	AssetManager::LoadTexture("cracked-bricks-3", "./assets/sprite/cracked-bricks-3.png");

	// Make the shape for rendering and add the texture
	// TODO: Don't do this
	shape = sf::RectangleShape(Hitbox.size);
	shape.setPosition(Hitbox.position);
	shape.setTexture(AssetManager::GetTexture("cracked-bricks-0"));

	// Set its properties
	HasCollision = true;
}

void CrackedBricks::Update()
{
	// Check for if we've been stepped on
	if (beenSteppedOn == false) return;

	// Update the timer
	timer += Utils::GetDeltaTime();

	if (cracked == false)
	{
		// Check for if the brick has cracked and
		// needs to begin falling
		if (timer >= timeBeforeBrickFalls)
		{
			cracked = true;
			timer = 0;

			// Remove collision so the player will also fall
			HasCollision = false;			
		}
	}
	else
	{
		// Respawn if the time is right
		if (timer >= timeBeforeBrickRespawns)
		{
			// Reset everything
			beenSteppedOn = false;
			cracked = false;
			HasCollision = true;
			timer = 0;

			// Go back to the uncracked texture
			shape.setTexture(AssetManager::GetTexture("cracked-bricks-0"));

			// Replace the brick
			Hitbox.position = initialPosition;
			shape.setPosition(Hitbox.position);
			yVelocity = 0.0f;
		}
	}

	// Make the brick fall if needed
	if (cracked)
	{
		yVelocity += Level::Gravity * Utils::GetDeltaTime();
		Hitbox.position.y += yVelocity * Utils::GetDeltaTime();
		shape.setPosition(Hitbox.position);
	}
}

void CrackedBricks::Draw()
{
	Utils::GetWindow()->draw(shape);
}

void CrackedBricks::Crack()
{
	// Can't be cracked twice
	if (beenSteppedOn == true) return;
	beenSteppedOn = true;
	timer = 0.f;

	// Change to the initial cracked state texture
	shape.setTexture(AssetManager::GetTexture("cracked-bricks-1"));
}