#include "numericalVectors.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "assetManager.h"
#include "logger.h"

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
		// If we're looking at a comment then skip the line
		if (currentLine._Starts_with("//")) continue;

		// Check for if we're entering a section. If we
		// have then move to the next line since there
		// is no 'logic' in a section
		if (EnteredSection(currentLine, section)) continue;

		// Check for if we're loading a texture
		if (section == SECTION_TEXTURES_KEY) LoadTexture(currentLine);

		// Check for if we're registering a tile
		if (section == SECTION_TILES_KEY) RegisterTile(currentLine);
	}

	// We're done with reading the file
	mapFile.close();
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
	tileTypes.push_back(tile);
	Logger::Log("Registered tile " + tile.Key + " with texture " + tile.TextureKey + " and " + std::to_string(tile.Tags.size()) + " tags");
}

void Map::LoadMapData(std::string line)
{
		
}

void Map::BakeLayer()
{

}