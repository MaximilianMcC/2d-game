#include "collisionHandler.h"

bool CollisionHandler::CollisionWithMap(sf::FloatRect thing, Map &map)
{
	// Get the tiles around the thing we're checking collision with
	// TODO: Just use a radius of one ngl
	std::vector<Tile> tiles = map.GetNeighbours(map.NearestTileCoordinateFromPosition(thing.position), 2);

	// Check for if theres collision with any of the tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		sf::FloatRect tile = sf::FloatRect(tiles[i].);
	}
	
}