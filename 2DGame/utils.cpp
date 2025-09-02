#include "utils.h"

// Register private static stuff
sf::RenderWindow* Utils::window;
float* Utils::deltaTime;

std::vector<std::string> Utils::Split(std::string string, std::string delimiter)
{
	std::vector<std::string> splitString;
	std::string currentToken;
 
	// Loop over every every character in the string
	for (size_t i = 0; i < string.length(); i++)
	{
		// Add the current character to our 'delimiter checker'
		currentToken += string[i];
 
		// Check for if we've got a full delimiter
		if (StringEndsWith(currentToken, delimiter) == false) continue;
 
		// Our delimiter string ends with the delimiter.
		// Remove the delimiter from the token, and add
		// it to the list to be returned
		currentToken.erase(currentToken.length() - delimiter.length());
		splitString.push_back(currentToken);
 
		// Reset the token for next time
		currentToken.clear();
	}
 
	// Add whatever we're left with to the
	// list of split things if we've already
	// found more than one split
	if (splitString.size() != 0) splitString.push_back(currentToken);
 
	// Give back the string
	return splitString;
}
 
bool Utils::StringEndsWith(std::string string, std::string ending)
{
	// The ending must be able to 'fit' inside
	// the string it's being searched for in
	if (ending.length() > string.length()) return false;
 
	// 'trim' the string and check for if
	// the end string is in it
	return (string.compare(
		string.length() - ending.length(),
		ending.length(),
		ending
	) == 0);
}

sf::Vector2f Utils::IndexToCoordinates(int index, int width)
{
	return sf::Vector2f(
		index % width,
		index / width
	);
}
