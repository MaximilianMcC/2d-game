#include "numericalVectors.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "assetManager.h"
#include "logger.h"

const sf::Vector2f Map::TileSize = { 32.f, 32.f };
std::vector<std::string> Map::tempTileTextures;
int Map::mapWidth = 0;
int Map::mapHeight = 0;
std::string Map::mapName;

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

		// Check for if we're entering a section
		if (EnteredSection(currentLine, section) == true) continue;
	}

	// We're done with reading the file
	mapFile.close();
}

bool Map::EnteredSection(std::string line, std::string& sectionKeeper)
{
	// Check for if we're entering a section
	if (line._Starts_with(">") == false) return false;

	// Update the section
	// TODO: Maybe use [0]
	sectionKeeper = Utils::Split(line, ">")[1];
	Logger::Log("Entering section " + sectionKeeper);

	// We have changed section
	return true;
}

void Map::LoadTexture(std::string line)
{
	
}

void Map::ParseTiles(std::string line)
{

}

void Map::BakeLayer()
{

}