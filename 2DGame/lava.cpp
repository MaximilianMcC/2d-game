#include "lava.h"

// TODO: Don't do this since its ugly as
Lava::Lava(sf::Vector2f position)
	: AnimatedTile(
		{ "./assets/sprite/lava-0.png", "./assets/sprite/lava-1.png", "./assets/sprite/lava-2.png" },
		1.0f,
		position,
		true
	)
{}