#include "player.h"

void Player::Start()
{
	body = sf::RectangleShape({ 100, 100 });
}

void Player::Update()
{
	body.move({ 100 * Utils::GetDeltaTime(), 0 });
}

void Player::Draw()
{
	Utils::GetWindow()->draw(body);
}
