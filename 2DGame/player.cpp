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

	// TODO: Do this in the H
	Speed = 250.f;
	JumpForce = 120.f;
}

void Player::Update()
{
	// Get the players movement direction
	//! Normalising isn't needed here ngl but good to have it
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) direction.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) direction.x++;
	if (direction.length() != 0) direction = direction.normalized();

	// Apply gravity
	if (onTheGroundRn == false)
	{
		// Add to the velocity value
		// TODO: Maybe don't times by delta time?
		yVelocity += Level::Gravity * Utils::GetDeltaTime();
	}

	// Check for if the player wants to jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		// No double jumping
		// TODO: Use guard clause
		if (onTheGroundRn)
		{
			// Apply the jump force in the opposite direction of gravity
			yVelocity -= JumpForce;
		}
	}

	// If we're in the air then half horizontal speed
	float speed = onTheGroundRn ? Speed : Speed / 2;

	// Calculate the new movement
	sf::Vector2f velocity = (direction * speed) + sf::Vector2f(0.0f, yVelocity);
	sf::FloatRect newHitbox = sf::FloatRect(Hitbox.position + velocity * Utils::GetDeltaTime(), Hitbox.size);
	CollisionInfo collisionInfo = SolveCollision(newHitbox, velocity);

	// Check for if the player is in the air or not
	if (collisionInfo.Bottom == true)
	{
		// Reset Y velocity (newten 5rd lore or something)
		yVelocity = 0.0f;
		onTheGroundRn = true;
	}
	else onTheGroundRn = false;

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
Player::CollisionInfo Player::SolveCollision(sf::FloatRect &newHitbox, sf::Vector2f direction)
{
	// Remember what we've hit
	CollisionInfo collisionInfo = {};

	// Check for collisions on the X
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
		if (direction.x < 0)
		{
			newXHitbox.position.x = thing->Hitbox.position.x + Level::TileSize.x;
			collisionInfo.Left = true;
		}
		if (direction.x > 0)
		{
			newXHitbox.position.x = thing->Hitbox.position.x - Level::TileSize.x;
			collisionInfo.Right = true;
		}
	}

	// Check for collisions on the Y
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
		if (direction.y < 0)
		{
			newYHitbox.position.y = thing->Hitbox.position.y + Level::TileSize.y;
			collisionInfo.Top = true;
		} 
		if (direction.y > 0)
		{
			newYHitbox.position.y = thing->Hitbox.position.y - Level::TileSize.y;
			collisionInfo.Bottom = true;
		} 
	}

	// Make the new hitbox based off the two seprate ones
	newHitbox.position = sf::Vector2f(newXHitbox.position.x, newYHitbox.position.y);

	// Give back the collision data
	return collisionInfo;
}