#pragma once

#include <string>

class GameObject
{
private:
	std::string name;

public:
	virtual void Start() { }
	virtual void Update() { }
	virtual void Draw() { }
	virtual void DrawUi() { }
	virtual void CleanUp() { }

	std::string GetName() { return name; }
	void SetName(std::string newName) { name = newName; }
};