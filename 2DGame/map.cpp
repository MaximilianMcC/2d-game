#include "numericalVectors.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "assetManager.h"

const sf::Vector2f Map::TileSize = { 32.f, 32.f };
std::vector<std::string> Map::tempTileTextures;
int Map::mapWidth = 0;
int Map::mapHeight = 0;
std::string Map::mapName;

void Map::LoadFromFile(std::string mapPath)
{
	// Open the map file
	std::ifstream mapFile(mapPath);
	if (!mapFile.is_open())
	{
		std::cerr << "issue opening map file at \"" << mapPath << "\"\n";
		return;
	}

	// Store our current state in the map
	std::string currentSection;
	int currentLayerIndex = -1;
	std::vector<std::string> currentLayerTextures;
	mapWidth = -1;
	mapHeight = -1;

	// Loop through every line
	std::string currentLine;
	while (std::getline(mapFile, currentLine))
	{
		// Check for if we're entering a section
		if (currentLine._Starts_with(">"))
		{
			// Figure out what section
			std::string tagName = Utils::Split(currentLine, ">")[1];
			if (tagName == TAG_TEXTURE) currentSection = TAG_TEXTURE;
			else if (tagName == TAG_LAYER)
			{
				//! maybe use [1] instead of [0]
				currentSection = TAG_LAYER;
				mapName = Utils::Split(tagName, TAG_LAYER)[0];
			}

			continue;
		}

		// Check for if we're exiting a section
		if (currentLine._Starts_with("<"))
		{
			// Figure out what section
			std::string tagName = Utils::Split(currentLine, ">")[1];
			if (tagName == TAG_LAYER)
			{
				// Bake the layer
				BakeLayer();

				// Reset everything for a new layer
				mapWidth = -1;
				mapHeight = -1;
				tempTileTextures.clear();
			}

			continue;
		}
	}

	// We're done with reading the file
	mapFile.close();
}

void Map::LoadTexture(std::string line)
{
	// Split the texture line to extract the
	// textures index and the texture path
	//? `0 ./test.png`
	std::vector<std::string> texture = Utils::Split(line, " ");

	// Load the texture using its key/index
	AssetManager::LoadTexture(MAP_TEXTURE_PREFIX + texture[0], texture[1]);
}

void Map::ParseTiles(std::string line)
{
	// Tile format:
	//? `<TEXTURE_INDEX>;`
	//? `<TEXTURE_INDEX>,TAG1,TAG2,TAG3;`

	// We are now on a new row
	mapHeight++;

	// Loop through every tile in the row
	std::vector<std::string> rawTiles = Utils::Split(line, ";");
	for (int i = 0; i < rawTiles.size(); i++)
	{
		// Extract all the info
		std::vector<std::string> tileData = Utils::Split(rawTiles[i], ",");
		mapWidth++;

		// First get the tiles texture
		std::string textureKey = MAP_TEXTURE_PREFIX + tileData[0];
		tempTileTextures.push_back(textureKey);

		// Then if the tile has any data handle accordingly
		if (tileData.size() > 1)
		{
			// Make a tile object so we can
			// store the data that it holds
			Tile tile;
			tile.Position = sf::Vector2i(mapWidth, mapHeight);

			// Loop over its attributes and add them
			//? starting at 1 since we already got the texture
			std::vector<std::string> attributes;
			for (int i = 1; i < tileData.size(); i++)
			{
				// TODO: Make a method that does this
				attributes.push_back(tileData[i]);
			}
			tile.Attributes = attributes;
		}
	}
}

void Map::BakeLayer()
{
	// Make a render texture for us to draw
	// the map to so we don't have to do 1000
	// draw calls every frame for zero reason
	sf::RenderTexture renderTexture(sf::Vector2u(mapWidth, mapHeight));

	// Use a tile to 'stamp' the textures with
	sf::RectangleShape stamp(TileSize);
	std::string previousTexture = "i am lowk writing this code on a plane rn";

	// Loop over every tile in the map
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			// Get the current texture
			int tileIndex = Utils::CoordinatesToIndex(sf::Vector2f(x, y), mapWidth);
			std::string currentTextureKey = tempTileTextures[tileIndex];

			// Check for if we need to change the texture
			if (currentTextureKey != previousTexture)
			{
				// Set the new texture
				stamp.setTexture(AssetManager::GetTexture(currentTextureKey));
				previousTexture = currentTextureKey; 
			}

			// Draw the texture on the map
			stamp.setPosition(sf::Vector2f(x, y) * TileSize);
			renderTexture.draw(stamp);
		}	
	}

	// The map has been drawn. Bake it to a texture
	AssetManager::TextureFromRenderTexture(MAP_PREFIX + mapName, renderTexture);
}