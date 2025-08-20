#include "forklift.h"
#include "assetManager.h"

void Forklift::Start()
{
	// Load all the sprites
	forklift = new sf::Sprite(*AssetManager::LoadAndGetTexture("Forklift", "./assets/sprite/forklift.png"));
	fork = new sf::Sprite(*AssetManager::LoadAndGetTexture("Fork", "./assets/sprite/fork.png"));
	wheelLeft = new sf::Sprite(*AssetManager::LoadAndGetTexture("WheelLeft", "./assets/sprite/wheel-left.png"));
	wheelRight = new sf::Sprite(*AssetManager::LoadAndGetTexture("WheelRight", "./assets/sprite/wheel-right.png"));

	// Load the sound
	hydraulicSound = new sf::Sound(*AssetManager::LoadAndGetSound("Hydraulic", "./assets/audio/hydraulic.wav"));
	engineSound = new sf::Sound(*AssetManager::LoadAndGetSound("Diesel", "./assets/audio/diesel-engine.wav"));
	reversingSound = new sf::Sound(*AssetManager::LoadAndGetSound("Reverse", "./assets/audio/reversing.wav"));
	reversingSound->setLooping(true);

	// Lowk just play the engine sound all the time
	engineSound->setLooping(true);
	engineSound->play();

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
	// position = { 200, 200 };
	position = { 700, 200 };
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

	// If we didn't move then stop the sound
	if (direction == 0) hydraulicSound->stop();

	// Otherwise start the sound if we're
	// not already playing it right now
	// TODO: Different pitch for going up/down
	if (hydraulicSound->getStatus() != sf::Sound::Status::Playing) hydraulicSound->play();

	// If its gone beyond the bounds then
	// snap it to the top/bottom so it is
	// 'attached' to the lift yk
	if (forkPosition > liftHeight)
	{
		forkPosition = liftHeight;
		hydraulicSound->stop();
	}
	if (forkPosition < 0)
	{
		forkPosition = 0;
		hydraulicSound->stop();
	}

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

	// If we're going backwards and we're not already
	// playing a sound then start the reversing sound
	if (reversingSound->getStatus() != sf::Sound::Status::Playing) reversingSound->play();

	// If we're not going backwards anymore stop the sound
	// TODO: Definitions for LEFT -1
	if (direction != -1) reversingSound->stop();
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

	delete hydraulicSound;
	hydraulicSound = nullptr;

	delete engineSound;
	engineSound = nullptr;

	delete reversingSound;
	reversingSound = nullptr;
}