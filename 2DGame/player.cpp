#include "player.h"
#include "level.h"
#include "assetManager.h"

Player::Player(sf::Vector2f spawnPoint)
{
	// Make the hitbox
	Hitbox = sf::FloatRect(spawnPoint, Level::TileSize);

	// Body
	body = sf::RectangleShape(Hitbox.size);
	body.setPosition(Hitbox.position);
	body.setTexture(AssetManager::LoadAndGetTexture("player", "./assets/sprite/player.png"));

	Speed = 100.f;
}

void Player::Update()
{
	sf::Vector2f movement;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) movement.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) movement.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) movement.y++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) movement.y--;

	// Update the hitbox
	if (movement.length() != 0) movement = movement.normalized();
	Hitbox.position += movement * Speed * Utils::GetDeltaTime();
	body.setPosition(Hitbox.position);
}

void Player::Draw()
{
	Utils::GetWindow()->draw(body);
}

void Player::CleanUp()
{
	
}
