#include "Console.h"

Console::~Console()
{
	//m_Window->DeleteAllChildrens();
	std::cout << "[~Console] Deconstructing...\n";
}

void Console::Init()
{
	int width = GetScreenWidth() / 3;
	int	height = GetScreenHeight() / 3;
	int x = (GetScreenWidth() - width) / 2; 
	int y = (GetScreenHeight() - height) / 2;
	Color color = { 100, 100, 120, 255 };

	m_Window = ComponentsManager::GetInstance().CreateComponent<ecs::Rectangle>(x, y, width, height, color);
	m_Topbar = ComponentsManager::GetInstance().CreateComponent<ecs::Rectangle>(0, 0, width, 50, Color{255, 100, 120, 100});
	m_Topbar->SetParent(m_Window);

	m_Window->SetName("[Console::Window]");
	m_Topbar->SetName("[Console::Topbar]");
}

void Console::OnFrame()
{
	if (IsKeyPressed(TOGGLE_CONSOLE_KEY))
	{
		m_Window->SetDrawable(!m_Window->IsDrawable());
	}
}
