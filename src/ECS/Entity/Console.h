#pragma once

// TODO: Absolute path
#include "../../ECS/Components/Base/ComponentsManager.h"
#include "../../ECS/Components/Rectangle.h"

class Console
{
public:
	void Init();
	void OnFrame();

private:
	std::shared_ptr<ecs::Rectangle> m_Window;
	std::shared_ptr<ecs::Rectangle> m_Topbar;
};