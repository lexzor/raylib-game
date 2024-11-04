#pragma once

// TODO: Absolute path
#include "../../ECS/Components/Base/ComponentsManager.h"
#include "../../ECS/Components/Rectangle.h"
#include "../../ECS/Components/Text.h"
#include <vector>

static unsigned char TOGGLE_CONSOLE_KEY = 96;

class Console
{
public:
	~Console();
	void Init();
	void OnFrame();

private:
	std::shared_ptr<ecs::Rectangle> m_Window = nullptr;
	std::shared_ptr<ecs::Rectangle> m_Topbar = nullptr;
	std::shared_ptr<ecs::Text> m_Title = nullptr;
	std::shared_ptr<ecs::Text> m_CloseButton = nullptr;

	bool m_MouseFirstButtonPressed = false;
	Vector2 m_LastFrameMousePos = { 0.0, 0.0 };

	std::vector<std::string> m_Messages;
};