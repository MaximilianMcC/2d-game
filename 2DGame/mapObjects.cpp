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
	BlocksMovement = hasCollision;
}

void Tile::Draw()
{
	Utils::GetWindow()->draw(shape);
};

AnimatedTile::AnimatedTile(std::vector<std::string> texturePaths, float animationFps, sf::Vector2f position, bool hasCollision)
{
	// Make the hitbox
	Hitbox = sf::FloatRect(position, Level::TileSize);

	// Make the shape for rendering
	// TODO: Don't do this
	shape = sf::RectangleShape(Hitbox.size);
	shape.setPosition(Hitbox.position);

	// Load all the textures
	for (std::string texturePath : texturePaths)
	{
		// TODO: Don't use the path as the key
		AssetManager::LoadTexture(texturePath, texturePath);
	}
	textureKeys = texturePaths;

	// Set its properties
	BlocksMovement = hasCollision;
	fps = 1.0f / animationFps;

	// Set the initial texture
	textureIndex = 0;
	shape.setTexture(AssetManager::GetTexture(textureKeys[textureIndex]));
}

void AnimatedTile::Draw()
{
	// Work the timer
	timer += Utils::GetDeltaTime();

	// Check for if we need to switch texture
	if (timer >= fps)
	{
		// Figure out what texture we need
	    textureIndex = (textureIndex + 1) % textureKeys.size();
		shape.setTexture(AssetManager::GetTexture(textureKeys[textureIndex]));
		timer = 0;
	}

	// Draw the actual tile
	Utils::GetWindow()->draw(shape);
}

void DynamicMapObject::CreateDefaultHitbox(sf::Vector2f position, bool blocksMovement)
{
	// Make the hitbox
	Hitbox = sf::FloatRect(position, Level::TileSize);

	// Set its properties
	BlocksMovement = blocksMovement;

	// Make the shape for rendering and add the texture
	// TODO: Don't do this
	shape = sf::RectangleShape(Hitbox.size);
	shape.setPosition(Hitbox.position);
}

void DynamicMapObject::Draw()
{
	Utils::GetWindow()->draw(shape);
}
