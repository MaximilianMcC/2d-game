#include "numericalVectors.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "assetManager.h"
#include "logger.h"
#include <algorithm>

const sf::Vector2f Map::TileSize = { 32.f, 32.f };

void Map::LoadFromFile(std::string mapPath)
{
	Logger::Log("Loading map file");

	// Open the map file
	std::ifstream mapFile(mapPath);
	if (!mapFile.is_open())
	{
		std::cerr << "issue opening map file at \"" << mapPath << "\"\n";
		return;
	}

	// Keep track of what 'section' we're in
	std::string section = "UNKNOWN";

	// Loop through every line
	std::string currentLine;
	while (std::getline(mapFile, currentLine))
	{
		// If we're looking at a comment or nothing then skip the line
		if (currentLine._Starts_with("//")) continue;
		if (currentLine.empty() == true) continue;

		// Check for if we're entering a section. If we
		// have then move to the next line since there
		// is no 'logic' in a section
		if (EnteredSection(currentLine, section)) continue;

		// Check for if we're loading a texture
		// TODO: Use switch for all this
		if (section == SECTION_TEXTURES_KEY) LoadTexture(currentLine);

		// Check for if we're registering a tile
		if (section == SECTION_TILES_KEY) RegisterTile(currentLine);

		// Check for if we're building the actual map
		if (section == SECTION_MAP_KEY) LoadMapData(currentLine);

		// Check for if we're done reading the map and
		// save it with a name and whatnot
		if (section == SECTION_NAME_KEY)
		{
			SetName(currentLine);
			BakeMap();
		}
	}

	// We're done with reading the file
	mapFile.close();
	Logger::Log("Loaded " + mapName + " thats " + std::to_string(mapWidth) + "x" + std::to_string(mapHeight) + " tiles.");
}

Tile Map::GetTile(sf::Vector2f coordinates)
{
    return mapTiles[Utils::CoordinatesToIndex(coordinates, mapWidth)];
}

int Map::GetMapLength()
{
	return mapWidth * mapHeight;
}

bool Map::EnteredSection(std::string line, std::string& sectionKeeper)
{
	// Check for if we're entering a section
	if (line._Starts_with(">") == false) return false;

	// Update the section
	sectionKeeper = Utils::Split(line, ">")[1];
	Logger::Log("Entering section " + sectionKeeper);

	// We have changed section
	return true;
}

void Map::LoadTexture(std::string line)
{
	// Parse and extract the texture data
	std::vector<std::string> data = Utils::Split(line, " ");
	if (data.size() < 2) return;
	std::string key = MAP_TEXTURE_PREFIX + data[0];

	// Load the texture
	AssetManager::LoadTexture(key, data[1]);
	Logger::Log("Loaded texture " + data[1] + " with key " + key);
}

void Map::RegisterTile(std::string line)
{
	// Parse the tile data
	std::vector<std::string> data = Utils::Split(line, " ");
	if (data.size() < 2) return;

	// If there are any tags then convert them
	// from a string into a string array
	std::vector<std::string> tags;
	if (data.size() > 2) tags = Utils::Split(data[2], ",");

	// Make, then register the tile
	Tile tile = {
		data[0],
		data[1],
		tags
	};
	tileTypePrefabs.push_back(tile);
	Logger::Log("Registered tile " + tile.Key + " with texture " + tile.TextureKey + " and " + std::to_string(tile.Tags.size()) + " tags");
}

void Map::LoadMapData(std::string line)
{
	// Extract the entire row of tiles
	std::vector<std::string> tiles = Utils::Split(line, ",");

	// Update the size of the map (dynamic as we read it)
	if (tiles.size() > mapWidth) mapWidth = tiles.size();
	mapHeight++;

	// Loop over each tile
	for (int i = 0; i < std::min((int)tiles.size(), mapWidth); i++)
	{
		// Find the tile we're after
		// TODO: Store the tiles in a dictionary instead of list
		Tile tile;
		for (int j = 0; j < tileTypePrefabs.size(); j++)
		{
			if (tileTypePrefabs[j].Key == tiles[i]) tile = tileTypePrefabs[j];
		}
		
		// Add it to the map
		mapTiles.push_back(tile);
	}
}

void Map::SetName(std::string line)
{
	// erhm
	mapName = line;
	Logger::Log("Loaded all data for map: " + mapName);
}

void Map::BakeMap()
{
	// Make the render texture to be baked
	sf::Vector2u mapSize = static_cast<sf::Vector2u>(TileSize * sf::Vector2f(mapWidth, mapHeight));
	sf::RenderTexture renderTexture = sf::RenderTexture(mapSize);

	// Make the 'stamp' for drawing with
	sf::RectangleShape stamp = sf::RectangleShape(TileSize);
	std::string currentTextureKey;

	// Loop over every tile in the map
	for (int i = 0; i < GetMapLength(); i++)
	{
		// Get the tile we're gonna draw rn
		std::string& tileTextureKey = mapTiles[i].TextureKey;

		// Check for if we need to change texture
		if (tileTextureKey != currentTextureKey)
		{
			// Set the texture
			stamp.setTexture(AssetManager::GetTexture(tileTextureKey));
			currentTextureKey = tileTextureKey;
		}

		// Add the tile to the map
		stamp.setPosition(Utils::CoordinatesFromIndex(i, mapWidth) * TileSize.x);
		renderTexture.draw(stamp);
	}

	// Bake the entire map to a texture
	AssetManager::LoadTextureFromRenderTexture(MAP_TEXTURE_PREFIX + mapName, renderTexture);
	Logger::Log("Baked map to texture");
}