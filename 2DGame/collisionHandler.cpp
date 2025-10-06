#include "collisionHandler.h"

bool CollisionHandler::WasCollisionWithMap(sf::FloatRect thing, Map &map)
{
	// Get the tiles around the thing we're checking collision with
	// TODO: Just use a radius of one ngl
	std::vector<Tile> tiles = map.GetNeighbours(map.NearestTileCoordinateFromPosition(thing.position), 2);

	// Check for if theres collision with any of the tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		// Make the tiles collision bounds
		sf::FloatRect tile = sf::FloatRect(tiles[i].Position, Map::TileSize);

		// Check for collision
		std::optional<sf::FloatRect> collision = thing.findIntersection(tile);
		if (collision.has_value() == false) continue;

		// We collided with somehting
		// TODO: Return the collision rectangle
		return true;
	}

	// There was no collision
	return false;
}