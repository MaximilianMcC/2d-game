#include "map.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "assetManager.h"

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

	const std::string LAYER_TAG = "LAYER_";
	const std::string TEXTURE_TAG = "TEXTURES";

	// Loop through every line
	std::string currentLine;
	while (std::getline(mapFile, currentLine))
	{
		// Check for if we're entering
		// a new section thingy
		if (currentLine._Starts_with(">"))
		{
			// Get the section header (without the `>` at the start)
			currentSection = currentLine.erase(0, 1);

			// Check for if we're making a layer
			if (currentLine._Starts_with(LAYER_TAG))
			{
				// Make the layer and set its name
				//! this might not work (use index 1 or something idk)
				Layer layer;
				layer.Name = Utils::Split(currentLine, LAYER_TAG)[0];
				
				// Add the layer to the layers list
				layers.push_back(layer);
				currentLayerIndex++;
			}

			continue;
		}

		// Check for what section we're in
		if (currentSection == TEXTURE_TAG)
		{
			// Split the texture line to extract the
			// tetxures index and the texture path
			//? `0 ./test.png`
			std::vector<std::string> texture = Utils::Split(currentLine, " ");

			// Load the texture
			AssetManager::LoadTexture(TEXTURE_PREFIX + texture[0], texture[1]);
		}
		else if (currentSection._Starts_with(LAYER_TAG))
		{
			Layer& layer = layers[currentLayerIndex];

			// Loop through all tiles in the current row
			std::vector<std::string> rawTiles = Utils::Split(currentLine, ";");
			for (int i = 0; i < rawTiles.size(); i++)
			{
				// Check for if the current tile has
				// any attributes or is just a texture
				std::vector<std::string> attributes = Utils::Split(rawTiles[i], ",");
				if (attributes.size() <= 1)
				{
					// Make a new tile that holds the attributes
					Tile tile;
					tile.Attributes = attributes;
					tile.Position = sf::Vector2i(i, layer.Height);

					// Add the tile to the map/layer
					layer.Tiles.push_back(tile);
				}

				// Add the tile to the list of tiles for drawing at the end
				//? [0] should be the texture
				currentLayerTextures.push_back(attributes[0]);
			}
			
			// Update the height, and update the width if needed
			layer.Height++;
			if (rawTiles.size() > layer.Width) layer.Width = rawTiles.size();
		}

	}
	mapFile.close();
}