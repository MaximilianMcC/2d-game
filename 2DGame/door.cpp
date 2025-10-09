#include "door.h"
#include "level.h"
#include "assetManager.h"
#include "numericalVectors.h"
#include "lever.h"

Door::Door(sf::Vector2f position)
{
	// Make the hitbox
	//? is 1x2 and origin is -1 up
	Hitbox = sf::FloatRect(
		position - sf::Vector2f(0.f, 1.f) * Level::TileSize,
		sf::Vector2f(1.f, 2.f) * Level::TileSize
	);

	// Load both textures
	// TODO: Don't do this every time
	AssetManager::LoadTexture("door-opened", "./assets/sprite/door-opened.png");
	AssetManager::LoadTexture("door-closed", "./assets/sprite/door-closed.png");

	// Set its properties
	Opened = false;
	IsImpassable = true;

	// Make the shape for rendering and add the texture
	// TODO: Don't do this
	shape = sf::RectangleShape(Hitbox.size);
	shape.setPosition(Hitbox.position);
	shape.setTexture(AssetManager::GetTexture("door-closed"));
}

void Door::Draw()
{
	Utils::GetWindow()->draw(shape);
}

void Door::Open()
{
	Opened = true;
	IsImpassable = false;
	shape.setTexture(AssetManager::GetTexture("door-opened"));

	// TODO: play a sound
}

void Door::Close()
{
	Opened = false;
	IsImpassable = true;
	shape.setTexture(AssetManager::GetTexture("door-closed"));

	// TODO: play a sound
}