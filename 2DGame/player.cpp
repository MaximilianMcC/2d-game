#include "player.h"
#include "level.h"
#include "collisionHandler.h"
#include "assetManager.h"
#include "crackedBricks.h"
#include "lava.h"
#include "lever.h"

Player::Player(sf::Vector2f spawnPoint)
{
	// Make the hitbox
	Hitbox = sf::FloatRect(spawnPoint, Level::TileSize);
	IsImpassable = true;

	// Body
	body = sf::RectangleShape(Hitbox.size);
	body.setPosition(Hitbox.position);
	body.setTexture(AssetManager::LoadAndGetTexture("player", "./assets/sprite/player.png"));

	// TODO: Do this in the H
	Speed = 250.f;
	JumpForce = 120.f;
}

void Player::Update()
{
	// Let the player move around
	CollisionHandler::CollisionInfo collision = Move();

	// Check for if we are ontop of a falling brick
	// TODO: Do this in the brick class, not the player
	CrackedBricks* crackedBrick = dynamic_cast<CrackedBricks*>(collision.Victim);
	if (crackedBrick != nullptr && collision.Bottom)
	{
		crackedBrick->Crack();
	}

	// Check for if we're in lava
	Lava* lava = dynamic_cast<Lava*>(collision.Victim);
	if (lava != nullptr)
	{
		printf("dead");
	}

	// Check for if we flip a lever
	Lever* lever = dynamic_cast<Lever*>(collision.Victim);
	if (lever != nullptr)
	{
		// Make sure we press the use key
		if (JustInteracted()) lever->Flip(); 
	}

	// Update the players visual position
	// based on their actual position
	// TODO: Maybe put in Draw but also dont
	body.setPosition(Hitbox.position);
}

void Player::Draw()
{
	Utils::GetWindow()->draw(body);
}

void Player::CleanUp()
{
	
}

CollisionHandler::CollisionInfo Player::Move()
{
	// Get the players movement direction
	//! Normalising isn't needed here ngl but good to have it
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) direction.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) direction.x++;
	if (direction.length() != 0) direction = direction.normalized();

	// Apply gravity
	if (onTheGroundRn == false)
	{
		// Add to the velocity value
		// TODO: Maybe don't times by delta time?
		yVelocity += Level::Gravity * Utils::GetDeltaTime();
	}

	// Check for if the player wants to jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		// No double jumping
		// TODO: Use guard clause
		if (onTheGroundRn)
		{
			// Apply the jump force in the opposite direction of gravity
			yVelocity -= JumpForce;
		}
	}

	// If we're in the air then half horizontal speed
	float speed = onTheGroundRn ? Speed : Speed / 2;

	// Calculate the new movement
	sf::Vector2f velocity = (direction * speed) + sf::Vector2f(0.0f, yVelocity);
	sf::FloatRect newHitbox = sf::FloatRect(Hitbox.position + velocity * Utils::GetDeltaTime(), Hitbox.size);
	CollisionHandler::CollisionInfo collisionInfo = CollisionHandler::SolveCollisionWithWorld(Hitbox, newHitbox, velocity);

	// Check for if the player is in the air or not
	if (collisionInfo.Bottom == true)
	{
		// Reset Y velocity (newten 5rd lore or something)
		yVelocity = 0.0f;
		onTheGroundRn = true;
	}
	else onTheGroundRn = false;

	// Update the actual position
	Hitbox.position = newHitbox.position;

	// Give back the collision info so we
	// can detect where we are and whatnot
	return collisionInfo;
}

bool Player::JustInteracted()
{
	// Check for if we pressed the interraction key
	bool interacted = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift));

	// If we previously interacted then
	// Ignore this since it'd let us
	// spam/hold the interact key (bad)
	if (interacted && previouslyInteracted == false)
	{
		previouslyInteracted = true;
		return true;
	}

	// When we let go then reset
	if (interacted == false) previouslyInteracted = false;
	return false;
}
