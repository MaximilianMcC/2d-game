#pragma once

#include <SFML/Graphics.hpp>

class MapObject {
public:
	sf::FloatRect Hitbox;
	bool HasCollision;
};

// Used for stuff that doesn't move
class StaticMapObject : public MapObject { };

// Used for stuff that moves via logic
class DynamicMapObject : public MapObject { };
