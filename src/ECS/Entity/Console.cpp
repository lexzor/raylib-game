#include "Console.h"

void Console::Init()
{
	int width = GetScreenWidth() / 3;
	int	height = GetScreenHeight() / 3;
	int x = GetScreenWidth() / 2 - width / 2; 
	int y = GetScreenHeight() / 2 - height / 2;
	Color color = { 100, 100, 120, 255 };

	m_Window = ComponentsManager::GetInstance().CreateComponent<ecs::Rectangle>(100, 100, 400, 400, color);
	m_Topbar = ComponentsManager::GetInstance().CreateComponent<ecs::Rectangle>(x, y, width, 50, color);
	//m_Topbar->AddChildren(m_Window);

	m_Window->SetName("[Console::Window]");
	m_Topbar->SetName("[Console::Topbar]");

	std::cout << "Added components\n";
}

void Console::OnFrame()
{
}
