#include "lever.h"
#include "level.h"
#include "assetManager.h"

Lever::Lever(sf::Vector2f position, bool flipped)
{
	// Make the hitbox
	// TODO: Maybe make it a big large
	Hitbox = sf::FloatRect(position, Level::TileSize);

	// Load both textures
	// TODO: Don't do this every time
	AssetManager::LoadTexture("lever-up", "./assets/sprite/lever-up.png");
	AssetManager::LoadTexture("lever-down", "./assets/sprite/lever-down.png");

	// Set its properties
	IsImpassable = false;
	Flipped = flipped;

	// Make the shape for rendering and add the texture
	// TODO: Don't do this
	shape = sf::RectangleShape(Hitbox.size);
	shape.setPosition(Hitbox.position);
	shape.setTexture(AssetManager::GetTexture(Flipped ? "lever-down" : "lever-up"));
}

void Lever::Draw()
{
	Utils::GetWindow()->draw(shape);
}

void Lever::Flip()
{
	// Flip the lever
	Flipped = !Flipped;

	// Set the texture depending
	// on if its flipped or not
	shape.setTexture(AssetManager::GetTexture(Flipped ? "lever-down" : "lever-up"));

	// TODO: play a sound
}
