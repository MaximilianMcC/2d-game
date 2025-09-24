#include "assetManager.h"

std::map<std::string, sf::SoundBuffer> AssetManager::sounds;
std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Cursor> AssetManager::cursors;
std::map<std::string, sf::Image> AssetManager::images;
std::map<std::string, sf::Font> AssetManager::fonts;

// TODO: Like all this is copy pasted (don't)
void AssetManager::LoadTexture(std::string key, std::string path)
{
	// Load it
	sf::Texture texture;
	if (texture.loadFromFile(path) == false)
	{
		// If there was an issue then say
		// TODO: exit 1
		std::cerr << "Error loading texture at path '" << path << "' (looked in " << std::filesystem::current_path() << ")";
	}

	// The texture was loaded. Chuck it into
	// the dictionary so it may be used
	textures[key] = texture;
}

void AssetManager::LoadTexture(std::string key, sf::Image& image)
{
	// Create the texture from the image
	sf::Texture texture;
	texture.loadFromImage(image);

	// The texture was created. Chuck it into
	// the dictionary so it may be used
	textures[key] = texture;
}

// TODO: Like all this is copy pasted (don't)
sf::Texture* AssetManager::GetTexture(std::string key)
{
	// TODO: Check for if they key exists or not
	return &textures[key];
}

sf::Texture* AssetManager::LoadAndGetTexture(std::string key, std::string path)
{
	LoadTexture(key, path);
	return GetTexture(key);
}

// TODO: Like all this is copy pasted (don't)
void AssetManager::LoadImage(std::string key, std::string path)
{
	// Load it
	sf::Image image;
	if (image.loadFromFile(path) == false)
	{
		// If there was an issue then say
		// TODO: exit 1
		std::cerr << "Error loading image at path '" << path << "' (looked in " << std::filesystem::current_path() << ")";
	}

	// The image was loaded. Chuck it into
	// the dictionary so it may be used
	images[key] = image;
}

sf::Image* AssetManager::LoadAndGetImage(std::string key, std::string path)
{
	LoadImage(key, path);
	return GetImage(key);
}

// TODO: Like all this is copy pasted (don't)
sf::Image* AssetManager::GetImage(std::string key)
{
	// TODO: Check for if they key exists or not
	return &images[key];
}


void AssetManager::LoadDefaultFont(std::string key, std::string name)
{
	// Get the default windows font path
	// TODO: Don't make this so c-like
	char fontPath[MAX_PATH];
	SHGetFolderPathA(NULL, CSIDL_FONTS, NULL, 0, fontPath);

	// Get the requested font
	std::string path = std::string(fontPath) + "\\" + name + ".ttf";

	// Load it
	sf::Font font;
	if (font.openFromFile(path) == false)
	{
		// If there was an issue then say
		// TODO: exit 1
		std::cerr << "Error loading font at path '" << path << "' (looked in " << std::filesystem::current_path() << ")";
	}

	// The font was loaded. Chuck it into
	// the dictionary so it may be used
	fonts[key] = font;
}

sf::Font* AssetManager::GetFont(std::string key)
{
	// TODO: Check for if they key exists or not
	return &fonts[key];
}


void AssetManager::LoadSound(std::string key, std::string path)
{
	// Load the buffer
	sf::SoundBuffer buffer;
	if (buffer.loadFromFile(path) == false)
	{
		// If there was an issue then say
		// TODO: exit 1
		std::cerr << "Error loading sound at path '" << path << "' (looked in " << std::filesystem::current_path() << ")";
	}

	// The sound was loaded. Chuck it into
	// the dictionary so it may be used
	sounds[key] = buffer;
}

sf::SoundBuffer* AssetManager::LoadAndGetSound(std::string key, std::string path)
{
	LoadSound(key, path);
	return GetSound(key);
}

sf::SoundBuffer* AssetManager::GetSound(std::string key)
{
	return &sounds[key];
}

void AssetManager::LoadTextureFromRenderTexture(std::string key, sf::RenderTexture &renderTexture)
{
	// Convert the texture to an image to a texture
	// When this happens we make a new 'copy' of the
	// texture that is unrelated to the render texture
	// which means we can delete the render texture
	// once we've generated the final texture thing
	sf::Texture renderTextureTexture = renderTexture.getTexture();
	sf::Image image = renderTextureTexture.copyToImage();
	LoadTexture(key, image);
}
