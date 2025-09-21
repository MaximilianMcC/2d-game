#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#define TAG_TEXTURE "TEXTURES"
#define TAG_LAYER "LAYER_"

class Map
{
public:
	static const sf::Vector2f TileSize;

	Map(std::string mapPath)
	{
		LoadFromFile(mapPath);
	}

	struct Tile
	{
		sf::Vector2i Position;
		std::vector<std::string> Attributes;
	};

	void LoadFromFile(std::string mapPath);
	
private:

	// Stuff for parsing
	// TODO: Use a struct or even a MapParser class idk
	static std::vector<std::string> tempTileTextures;
	static int mapWidth;
	static int mapHeight;
	static std::string mapName;

	static void LoadTexture(std::string line);
	static void ParseTiles(std::string line);
	static void BakeLayer();
};