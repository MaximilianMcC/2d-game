#include "player.h"
#include "level.h"
#include "assetManager.h"

Player::Player(sf::Vector2f spawnPoint)
{
	// Make the hitbox
	Hitbox = sf::FloatRect(spawnPoint, Level::TileSize);

	// Body
	body = sf::RectangleShape(Hitbox.size);
	body.setPosition(Hitbox.position);
	body.setTexture(AssetManager::LoadAndGetTexture("player", "./assets/sprite/player.png"));

	Speed = 250.f;
}

void Player::Update()
{
	sf::Vector2f movement;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) movement.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) movement.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) movement.y++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) movement.y--;

	// Update the hitbox
	if (movement.length() != 0) movement = movement.normalized();
	sf::FloatRect newHitbox = sf::FloatRect(Hitbox.position + movement * Speed * Utils::GetDeltaTime(), Hitbox.size);

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

		if (movement.x < 0) newXHitbox.position.x = thing->Hitbox.position.x + Level::TileSize.x;
		if (movement.x > 0) newXHitbox.position.x = thing->Hitbox.position.x - Level::TileSize.x;
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

		if (movement.y < 0) newYHitbox.position.y = thing->Hitbox.position.y + Level::TileSize.y;
		if (movement.y > 0) newYHitbox.position.y = thing->Hitbox.position.y - Level::TileSize.y;
	}

	newHitbox.position = sf::Vector2f(newXHitbox.position.x, newYHitbox.position.y);

	// Update the actual collision
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
