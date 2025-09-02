#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Map
{
public:
	Map(std::string mapPath)
	{
		LoadFromFile(mapPath);
	}

	struct Tile
	{
		std::vector<std::string> Attributes;
		sf::Vector2i Position;
	};

	struct Layer
	{
		std::string Name;
		int Width;
		int Height;

		// Only tiles with attributes are stored
		std::vector<Tile> Tiles;

		sf::Texture Texture;
		sf::RenderTexture RenderTexture;
	};

	void LoadFromFile(std::string mapPath);
	
private:
	const std::string TEXTURE_PREFIX = "MAP_";

	std::vector<Layer> layers;
};