#include "Application.h"
#include "ResourceManager.h"
#include "DeveloperConsole.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	InitWindow(1300, 800, "TagME!");
	DisableCursor();

	//SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	ResourceManager::GetInstance().PrecacheFont("coolvetica_regular.otf");
	ResourceManager::GetInstance().PrecacheFont("bebas_neue_regular.otf");

	m_GUI.Init();
	DeveloperConsole::GetInstance().SetConsole(m_GUI.GetConsole());

	m_Commands.Init();
}

void Application::Run()
{

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground({ 0, 0, 0, 255 });
		DrawFPS(10, 10);

		m_Camera.BeginCameraDraw();
		DrawGrid(20, 1.0f); // Draw a grid for orientation
		DrawCube({ 0, 1, 0 }, 1, 1, 1, RED); // Sample object in the scene
		m_Camera.OnFrame();
		m_Camera.EndCameraDraw();
		OnFrame();
		
		EndDrawing();
	}

	CloseWindow();
}

void Application::OnFrame()
{
	m_GUI.OnFrame();
	m_Renderer.Draw();
}
