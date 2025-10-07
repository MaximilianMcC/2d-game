#pragma once

#include <SFML/Graphics.hpp>

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