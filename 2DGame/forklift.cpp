#include "forklift.h"
#include "assetManager.h"

void Forklift::Start()
{
	// Load all the sprites
	forklift = new sf::Sprite(*AssetManager::LoadAndGetTexture("Forklift", "./assets/sprite/forklift.png"));
	fork = new sf::Sprite(*AssetManager::LoadAndGetTexture("Fork", "./assets/sprite/fork.png"));
	wheelLeft = new sf::Sprite(*AssetManager::LoadAndGetTexture("WheelLeft", "./assets/sprite/wheel-left.png"));
	wheelRight = new sf::Sprite(*AssetManager::LoadAndGetTexture("WheelRight", "./assets/sprite/wheel-right.png"));

	// Setup the fork stuff
	// TODO: Do this more 'mathematically' or something idk
	liftHeight = 175.f;
	forkOriginOffset = { 180.f, 180.f };

	// Set the wheels origin to be in their centre
	// TODO: Make a wheel struct or something
	wheelLeft->setOrigin(wheelLeft->getLocalBounds().size * sf::Vector2f(0.5f, 0.5f));
	wheelRight->setOrigin(wheelRight->getLocalBounds().size * sf::Vector2f(0.5f, 0.5f));

	// Set the wheel positions
	wheelLeftPosition = sf::Vector2f(20.f, 190.f ) + wheelLeft->getOrigin();
	wheelRightPosition = sf::Vector2f(110.f, 190.f ) + wheelRight->getOrigin();

	// Set the initial position of the actual forklift
	position = { 200, 200 };
}

void Forklift::Update()
{
	MoveFork();
	Drive();
}

void Forklift::MoveFork()
{
	// Get the direction to move the fork
	int direction = 0;
	direction += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	direction -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

	// Move it
	forkPosition += (forkSpeed * direction) * Utils::GetDeltaTime();

	// If its gone beyond the bounds then
	// snap it to the top/bottom so it is
	// 'attached' to the lift yk
	if (forkPosition > liftHeight) forkPosition = liftHeight;
	if (forkPosition < 0) forkPosition = 0;

	// Update the actual position
	fork->setPosition(position + forkOriginOffset + sf::Vector2f(0, -forkPosition));
}

void Forklift::Drive()
{
	// Get the direction to dive in
	int direction = 0;
	direction -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
	direction += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

	// Move it
	// TODO: Make this force based
	float newMovement = (driveSpeed * direction) * Utils::GetDeltaTime();
	position.x += newMovement;

	// Turn the wheels in the relevant direction a bit
	wheelLeft->rotate(sf::degrees(newMovement));
	wheelRight->rotate(sf::degrees(newMovement));

	// Update the positions of everything
	// TODO: Make a method that does all this
	forklift->setPosition(position);
	wheelLeft->setPosition(position + wheelLeftPosition);
	wheelRight->setPosition(position + wheelRightPosition);
}

void Forklift::Draw()
{
	Utils::GetWindow()->draw(*fork);
	Utils::GetWindow()->draw(*forklift);

	Utils::GetWindow()->draw(*wheelLeft);
	Utils::GetWindow()->draw(*wheelRight);
}

void Forklift::CleanUp()
{
	delete forklift;
	forklift = nullptr;

	delete fork;
	fork = nullptr;

	delete wheelLeft;
	wheelLeft = nullptr;

	delete wheelRight;
	wheelRight = nullptr;
}