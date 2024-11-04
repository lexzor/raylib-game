#include "Console.h"
#include "../../ResourceManager.h"

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

	std::shared_ptr<Font> titleFont = ResourceManager::GetInstance().GetFontByName("bebas_neue_regular");

	m_Window = ComponentsManager::GetInstance().CreateComponent<ecs::Rectangle>(x, y, width, height, Color{ 100, 100, 120, 255 });
	m_Topbar = ComponentsManager::GetInstance().CreateComponent<ecs::Rectangle>(0, 0, width, 30, Color{120, 100, 135, 225});
	m_Title = ComponentsManager::GetInstance().CreateComponent<ecs::Text>(20, m_Topbar->height / 2 - 12 / 2, "Developer Console", 12, Color{ 255, 255, 255, 255 }, titleFont);
	m_CloseButton = ComponentsManager::GetInstance().CreateComponent<ecs::Text>(m_Topbar->GetTransform()->position.x + m_Topbar->width - 20, m_Topbar->height / 2 - 12 / 2, "X", 12, Color{255, 255, 255, 255}, titleFont);

	ComponentsManager::GetInstance().AddComponentChildren<ecs::Rectangle, ecs::Rectangle>(m_Window, m_Topbar);
	ComponentsManager::GetInstance().AddComponentChildren<ecs::Rectangle, ecs::Text>(m_Topbar, m_Title);
	ComponentsManager::GetInstance().AddComponentChildren<ecs::Rectangle, ecs::Text>(m_Topbar, m_CloseButton);

	m_Window->SetName("[Console::Window]");
	m_Topbar->SetName("[Console::Topbar]");
	m_Title->SetName("[Console::Title]");
	m_CloseButton->SetName("[Console::CloseButton]");
}

void Console::OnFrame()
{
	if (IsWindowResized())
	{
		m_Window->width = GetScreenWidth() / 3;
		m_Window->height = GetScreenHeight() / 3;
		//m_Window->GetTransform()->position.x = (GetScreenWidth() - m_Window->width) / 2.0;
		//m_Window->GetTransform()->position.y = (GetScreenHeight() - m_Window->height) / 2.0;
		m_Topbar->width = m_Window->width;
		m_CloseButton->GetTransform()->position.x = m_Topbar->GetTransform()->position.x + m_Topbar->width - 20;
	}

	if (IsKeyPressed(TOGGLE_CONSOLE_KEY))
	{
		m_Window->SetDrawable(!m_Window->IsDrawable());

		if (m_Window->IsDrawable())
		{
			m_Window->GetTransform()->position.x = (GetScreenWidth() - m_Window->width) / 2.0;
			m_Window->GetTransform()->position.y = (GetScreenHeight() - m_Window->height) / 2.0;
		}
	}

	if (m_Topbar->MouseHover())
	{
		if (m_CloseButton->MouseHover())
		{
			m_CloseButton->color = { 255, 0, 0, 255 };

			if (IsMouseButtonDown(0))
			{
				m_Window->SetDrawable(false);
			}
		}
		else
		{
			m_CloseButton->color = { 255, 255, 255, 255 };
		}

		m_Topbar->color = { 120, 100, 180, 225 };
	
		if (IsMouseButtonDown(0))
		{
			Vector2 newConsolePosition{};
			newConsolePosition.x = m_Window->GetTransform()->position.x + (GetMousePosition().x - m_LastFrameMousePos.x);
			newConsolePosition.y = m_Window->GetTransform()->position.y + (GetMousePosition().y - m_LastFrameMousePos.y);

			if(newConsolePosition.x + m_Window->width > 50 && newConsolePosition.x < GetScreenWidth() - 50
			&& newConsolePosition.y > 0 && newConsolePosition.y < GetScreenHeight() - m_Topbar->height)
			{
				m_Window->GetTransform()->position.x =  newConsolePosition.x;
				m_Window->GetTransform()->position.y =  newConsolePosition.y;
			}
		}
	}
	else
	{
		m_Topbar->color = { 120, 100, 135, 225 };
	}

	m_LastFrameMousePos = GetMousePosition();
}
