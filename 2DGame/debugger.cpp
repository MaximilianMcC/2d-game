#include "debugger.h"

sf::RenderWindow Debugger::Window;
std::vector<Debugger::Variable> Debugger::variables;

void Debugger::InitWindow()
{
	// Make the window
	Window = sf::RenderWindow(sf::VideoMode({ 400, 200 }), "debugger");

	// Load the font
	AssetManager::LoadDefaultFont("consolas", "consola");
}

void Debugger::RegisterVariable(float *variablePointer, std::string variableName, sf::Keyboard::Key increimentKey, sf::Keyboard::Key decreimentKey, float adjustAmount)
{
	// Make the label so we can see what the
	// value is and also change it easily
	const float padding = 10.f;
	const unsigned int fontSize = 16;
	sf::Text label(*AssetManager::GetFont("consolas"), "loading", fontSize);
	label.setPosition(sf::Vector2f(padding, padding + ((padding + (fontSize * 2)) * variables.size())));
	label.setFillColor(sf::Color::Black);
	
	// Add everything to the struct
	variables.push_back({
		variablePointer,
		label,
		variableName,
		increimentKey,
		decreimentKey,
		adjustAmount
	});
}

void Debugger::Update()
{
	// If we press ` or f3 open the debug menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Grave) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3))
	{
		// Make sure there isn't already a window open
		if (Window.isOpen() == false) InitWindow();
	}

	// If there isn't a window then don't do anything
	if (Window.isOpen() == false) return;

	// Loop over all variables
	for (size_t i = 0; i < variables.size(); i++)
	{
		// If their respecitve keys are pressed, modify the value
		if (sf::Keyboard::isKeyPressed(variables[i].IncreimentKey)) *(variables[i].Pointer) += variables[i].adjustAmount;
		if (sf::Keyboard::isKeyPressed(variables[i].DecreimentKey)) *(variables[i].Pointer) -= variables[i].adjustAmount;

		// Update the text to reflect the changes
		// TODO: Only do if changes were made
		char increimentKeyAscii = 'A' + ((int)variables[i].IncreimentKey - (int)sf::Keyboard::Key::A);
		char decreimentKeyAscii = 'A' + ((int)variables[i].DecreimentKey - (int)sf::Keyboard::Key::A);
		variables[i].Label.setString(variables[i].Name + " = " + std::to_string(*variables[i].Pointer) + "\n" + "(" + decreimentKeyAscii + " and " + increimentKeyAscii + ")");
	}
}

void Debugger::Draw()
{
	// Draw all the variables
	for (size_t i = 0; i < variables.size(); i++)
	{
		Window.draw(variables[i].Label);
	}
}
