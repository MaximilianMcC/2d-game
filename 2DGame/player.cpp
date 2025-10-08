#include "player.h"
#include "level.h"
#include "assetManager.h"

Player::Player(sf::Vector2f spawnPoint)
{
	// Make the hitbox
	Hitbox = sf::FloatRect(spawnPoint, Level::TileSize);
	HasCollision = true;

	// Body
	body = sf::RectangleShape(Hitbox.size);
	body.setPosition(Hitbox.position);
	body.setTexture(AssetManager::LoadAndGetTexture("player", "./assets/sprite/player.png"));

	Speed = 250.f;
}

void Player::Update()
{
	// Get the players direction
	//! Normalising isn't needed here ngl but good to have it
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) direction.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) direction.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) direction.y++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) direction.y--;
	if (direction.length() != 0) direction = direction.normalized();

	// Calculate the new movement
	sf::FloatRect newHitbox = sf::FloatRect(Hitbox.position + direction * Speed * Utils::GetDeltaTime(), Hitbox.size);
	SolveCollision(newHitbox, direction);

	// Update the actual position
	Hitbox.position = newHitbox.position;
	body.setPosition(Hitbox.position);
}

void Player::Draw()
{
	Utils::GetWindow()->draw(body);
}

void Player::CleanUp()
{
	
}

// TODO: Use the intersection results
void Player::SolveCollision(sf::FloatRect &newHitbox, sf::Vector2f direction)
{
	// Check for collisions
	sf::FloatRect newXHitbox = sf::FloatRect(sf::Vector2f(newHitbox.position.x, Hitbox.position.y), Level::TileSize);
	for (MapObject* thing : Level::MapObjects)
	{
		// Check for if the thingy has a collider
		if (thing->HasCollision == false) continue;

		// Check for collision
		std::optional<sf::FloatRect> potentialCollision = newXHitbox.findIntersection(thing->Hitbox);
		if (potentialCollision.has_value() == false) continue;
		sf::FloatRect collision = potentialCollision.value();

		// Adjust to prevent the actual collision
		if (direction.x < 0) newXHitbox.position.x = thing->Hitbox.position.x + Level::TileSize.x;
		if (direction.x > 0) newXHitbox.position.x = thing->Hitbox.position.x - Level::TileSize.x;
	}

	sf::FloatRect newYHitbox = sf::FloatRect(sf::Vector2f(Hitbox.position.x, newHitbox.position.y), Level::TileSize);
	for (MapObject* thing : Level::MapObjects)
	{
		// Check for if the thingy has a collider
		if (thing->HasCollision == false) continue;

		// Check for collision
		std::optional<sf::FloatRect> potentialCollision = newYHitbox.findIntersection(thing->Hitbox);
		if (potentialCollision.has_value() == false) continue;
		sf::FloatRect collision = potentialCollision.value();

		// Adjust to prevent the actual collision
		if (direction.y < 0) newYHitbox.position.y = thing->Hitbox.position.y + Level::TileSize.y;
		if (direction.y > 0) newYHitbox.position.y = thing->Hitbox.position.y - Level::TileSize.y;
	}

	// Make the new hitbox based off the two seprate ones
	newHitbox.position = sf::Vector2f(newXHitbox.position.x, newYHitbox.position.y);
}
