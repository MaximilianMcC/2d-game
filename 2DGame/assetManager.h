/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : assetManager
Description : load assets
Author : Maximilian Oscar Jack McCarthy
Mail : maximilian.mccarthy@mds.ac.nz
**************************************************************************/

#pragma once
#include <map>
#include <string>
#include <shlobj.h>
#include <iostream>
#include "utils.h"
#include <Windows.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define MAP_TEXTURE_PREFIX "MAP_TEXTURE_"
#define MAP_PREFIX "MAP_"

class AssetManager
{
private:
static std::map<std::string, sf::SoundBuffer> sounds;
static std::map<std::string, sf::Texture> textures;
static std::map<std::string, sf::Cursor> cursors;
static std::map<std::string, sf::Image> images;
static std::map<std::string, sf::Font> fonts;

public:
	static void LoadTexture(std::string key, std::string path);
	static void LoadTexture(std::string key, sf::Image& image);
	static sf::Texture* LoadAndGetTexture(std::string key, std::string path);
	static sf::Texture* GetTexture(std::string key);
	
	static void LoadImage(std::string key, std::string path);
	static sf::Image* LoadAndGetImage(std::string key, std::string path);
	static sf::Image* GetImage(std::string key);

	static void LoadDefaultFont(std::string key, std::string fontFileName);
	static sf::Font* GetFont(std::string key);

	static void LoadSound(std::string key, std::string path);
	static sf::SoundBuffer* LoadAndGetSound(std::string key, std::string path);
	static sf::SoundBuffer* GetSound(std::string key);

	static void LoadTextureFromRenderTexture(std::string key, sf::RenderTexture& renderTexture);
};