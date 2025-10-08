#include "crackedBricks.h"
#include "level.h"
#include "assetManager.h"
#include "utils.h"

CrackedBricks::CrackedBricks(sf::Vector2f position)
{
	// Make the hitbox
	Hitbox = sf::FloatRect(position, Level::TileSize);

	// Make the shape for rendering and add the texture
	// TODO: Don't do this
	shape = sf::RectangleShape(Hitbox.size);
	shape.setPosition(Hitbox.position);
	shape.setTexture(AssetManager::LoadAndGetTexture("cracked-bricks", "./assets/sprite/cracked-bricks.png"));

	// Set its properties
	HasCollision = true;
}

void CrackedBricks::Draw()
{
	Utils::GetWindow()->draw(shape);
}