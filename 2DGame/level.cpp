#include "level.h"

std::optional<sf::FloatRect> Level::GetCollision(MapObject &thing)
{
	// Loop over all map objects
	std::optional<sf::FloatRect> collision;
	for (int i = 0; i < MapObjects.size(); i++)
	{
		// Check for if we allow collision
		if (MapObjects[i].HasCollision == false) continue;

		// We cannot collide with ourself
		if (&MapObjects[i] == &thing) continue;

		// Get the actual collision
		collision = thing.Hitbox.findIntersection(MapObjects[i].Hitbox);
		if (collision.has_value()) break;
	}

	// Give back the float rect thing
	return collision;
}