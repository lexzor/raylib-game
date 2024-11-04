#include "Console.h"

void Console::Init()
{
	m_Window = ComponentsManager::GetInstance().CreateComponent<ecs::Rectangle>(500, 500, 100, 100, Color{255, 0, 0, 255});
}

void Console::OnFrame()
{
}
