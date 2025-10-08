#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class MapObject {
public:
	sf::FloatRect Hitbox;
	bool HasCollision;

	virtual void Draw() = 0;
};

// Used for stuff that doesn't move
class StaticMapObject : public MapObject
{
};

// Used for stuff that moves via logic
class DynamicMapObject : public MapObject
{
public:
	virtual void Update() { }
	virtual void Draw() { }
	virtual void CleanUp() { }
};





// TODO: Put in another file
class Tile : public StaticMapObject
{
private:
	sf::RectangleShape shape;
public:
	Tile(std::string textureKey, sf::Vector2f position, bool hasCollision);
	void Draw() override;
};

class AnimatedTile : public StaticMapObject
{
private:
	sf::RectangleShape shape;
	float timer;
	float fps;
	std::vector<std::string> textureKeys;
	int textureIndex;
public:
	AnimatedTile(std::vector<std::string> texturePaths, float animationFps, sf::Vector2f position, bool hasCollision);
	void Draw() override;
};