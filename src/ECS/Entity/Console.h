#pragma once

// TODO: Absolute path
#include "../../ECS/Components/Base/ComponentsManager.h"
#include "../../ECS/Components/Rectangle.h"

static unsigned char TOGGLE_CONSOLE_KEY = 96;

class Console
{
public:
	~Console();
	void Init();
	void OnFrame();

private:
	std::shared_ptr<ecs::Rectangle> m_Window;
	std::shared_ptr<ecs::Rectangle> m_Topbar;
};