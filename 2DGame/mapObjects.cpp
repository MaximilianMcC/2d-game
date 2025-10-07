#include "mapObjects.h"
#include "level.h"
#include "assetManager.h"
#include "utils.h"

Tile::Tile(std::string textureKey, sf::Vector2f position, bool hasCollision)
{
	// Make the hitbox
	Hitbox = sf::FloatRect(position, Level::TileSize);

	// Make the shape for rendering and add the texture
	// TODO: Don't do this
	shape = sf::RectangleShape(Hitbox.size);
	shape.setPosition(Hitbox.position);
	shape.setTexture(AssetManager::GetTexture(textureKey));

	// Set its properties
	HasCollision = hasCollision;
}

void Tile::Draw()
{
	Utils::GetWindow()->draw(shape);
};