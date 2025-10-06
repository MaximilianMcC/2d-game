#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#define SECTION_TEXTURES_KEY "TEXTURES"
#define SECTION_TILES_KEY "TILES"
#define SECTION_MAP_KEY "MAP"
#define SECTION_NAME_KEY "NAME"

struct TilePrefab
{
	std::string Key;
	std::string TextureKey;
	std::vector<std::string> Tags;
};

struct Tile : TilePrefab
{
	sf::Vector2f Position;

	Tile(const TilePrefab& prefab, sf::Vector2f position)
	: TilePrefab(prefab)
	{
		Position = position;
	}
};

class Map
{
public:
	static const sf::Vector2f TileSize;

	Map(std::string mapPath)
	{
		LoadFromFile(mapPath);
	}

	void LoadFromFile(std::string mapPath);

	Tile GetTile(sf::Vector2f coordinates);
	sf::Vector2f NearestTileCoordinateFromPosition(sf::Vector2f position);
	
	// The radius is a square btw (not a circle)
	std::vector<Tile> GetNeighbours(sf::Vector2f centreTile, int radius);

	int GetMapLength();
	sf::Texture* GetMapTexture();
	
	void Draw();

private:

	// Stuff for parsing
	// TODO: Use a struct or even a MapParser class idk
	// TODO: No -1
	int mapWidth = 0;
	int mapHeight = 0;
	std::string mapName;

	std::vector<TilePrefab> tileTypePrefabs;
	std::vector<TilePrefab> mapTiles;

	std::string GetTextureKey();

	bool EnteredSection(std::string line, std::string& sectionKeeper);
	void LoadTexture(std::string line);
	void RegisterTile(std::string line);
	void LoadMapData(std::string line);
	void SetName(std::string line);
	void BakeMap();
};