#pragma once

#include <string>

class GameObject
{
private:
	std::string name;

public:
	void Start() { }
	void Update() { }
	void Draw() { }
	void DrawUi() { }
	void CleanUp() { }

	std::string GetName() { return name; }
	void SetName(std::string newName) { name = newName; }
};