#include "collisionHandler.h"
#include "level.h"

// TODO: Use the intersection results
CollisionHandler::CollisionInfo CollisionHandler::SolveCollisionWithWorld(sf::FloatRect &hitbox, sf::FloatRect &newHitbox, sf::Vector2f direction)
{
	// Remember what we've hit
	CollisionInfo collisionInfo = {};
	collisionInfo.Victim = nullptr;

	// Check for collisions on the X
	sf::FloatRect newXHitbox = sf::FloatRect(sf::Vector2f(newHitbox.position.x, hitbox.position.y), Level::TileSize);
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
		else continue;

		// Say what we've collided with
		collisionInfo.Victim = thing;
	}

	// Check for collisions on the Y
	sf::FloatRect newYHitbox = sf::FloatRect(sf::Vector2f(hitbox.position.x, newHitbox.position.y), Level::TileSize);
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
		else continue;

		// Say what we've collided with
		collisionInfo.Victim = thing;
	}

	// Make the new hitbox based off the two seprate ones
	newHitbox.position = sf::Vector2f(newXHitbox.position.x, newYHitbox.position.y);

	// Give back the collision data
	return collisionInfo;
}