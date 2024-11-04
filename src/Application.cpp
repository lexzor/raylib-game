#include "Application.h"
#include "ResourceManager.h"

Application::Application()
{
}

Application::~Application()
{
	std::cout << "[~Application] Deconstructing..\n";
}

void Application::Init()
{

	SetWindowState(FLAG_WINDOW_RESIZABLE);
	InitWindow(1300, 800, "TagME!");

	SetTargetFPS(0);

	m_Console.Init();
	ResourceManager::GetInstance().PrecacheFont("coolvetica_regular.otf");
	ResourceManager::GetInstance().PrecacheFont("bebas_neue_regular.otf");
}

void Application::Run()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground({ 0, 0, 0, 255 });
		DrawFPS(10, 10);
		OnFrame();
		EndDrawing();
	}
}

void Application::OnFrame()
{
	m_Renderer.Draw();
	m_Console.OnFrame();
}
