#include "player.h"
#include <iostream>

void Player::Start()
{
	// Make the players body (temp debug)
	body = sf::RectangleShape({ 50, 50 });

	position = { 50, 100 };
	body.setPosition(position);
}

void Player::Update()
{
	// Get input
	int inputDirection = 0;
	inputDirection -= (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
	inputDirection += (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));

	// Update the players velocity
	float accelerationForce = acceleration * Utils::GetDeltaTime();
	velocity.x += accelerationForce * inputDirection;

	// If we're not moving then apply friction
	if ((inputDirection == 0) && (velocity.x != 0))
	{
		// Calculate how much force we'll apply
		float frictionForce = friction * Utils::GetDeltaTime();

		// If we're slow as then stop
		if (abs(velocity.x) < frictionForce) velocity.x = 0;
		else
		{
			// Get the direction the velocity is taking us and
			// apply friction in the opposite direction
			velocity.x += frictionForce * -GetDirection();
		}
	}

	// Make sure we're not breaking the sound barrier
	if (abs(velocity.x) > maxSpeed) velocity.x = maxSpeed * GetDirection();

	// Actually move the player
	// TODO: See if you can just give the body a pointer
	position += velocity * Utils::GetDeltaTime();
	body.setPosition(position);
}

void Player::Draw()
{
	Utils::GetWindow()->draw(body);
}
