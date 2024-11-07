#pragma once
#include "../ECS/Entity/Console.h"
#include <memory>

class GUI
{
public:
	GUI();
	~GUI();

	void Init();
	void OnFrame();
	std::shared_ptr<Console> GetConsole();

private:
	std::shared_ptr<Console> m_Console = nullptr;
};