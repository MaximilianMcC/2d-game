#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#define SECTION_TEXTURES_KEY "TEXTURES"
#define SECTION_TILES_KEY "TILES"
#define SECTION_MAP_KEY "MAP"

struct Tile
{
	std::string Key;
	std::string TextureKey;
	std::vector<std::string> Tags;
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
	
private:

	// Stuff for parsing
	// TODO: Use a struct or even a MapParser class idk
	int mapWidth;
	int mapHeight;
	std::string mapName;

	std::vector<Tile> tileTypes;

	bool EnteredSection(std::string line, std::string& sectionKeeper);
	void LoadTexture(std::string line);
	void RegisterTile(std::string line);
	void LoadMapData(std::string line);
	void BakeLayer();
};