#include "Application.h"
#include "ResourceManager.h"
#include "DeveloperConsole.h"
#include "ECS/Components/Model.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	//SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	InitWindow(1300, 800, "TagME!");
	//SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
	DisableCursor();

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	ResourceManager::get().PrecacheFont("coolvetica_regular.otf");
	ResourceManager::get().PrecacheFont("bebas_neue_regular.otf");

	m_GUI.Init();
	DeveloperConsole::get().SetConsole(m_GUI.GetConsole());

	m_Commands.Init();
	m_EntityCreator.Init();
}

void Application::Run()
{
	ResourceManager::get().PrecacheModel("map/tile-dirt.obj");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground({ 0, 0, 0, 255 });
		m_Camera.BeginCameraDraw();
		DrawGrid(20, 1.0f); // Draw a grid for orientation
		m_Camera.OnFrame();
		m_EntityCreator.OnFrame();
		m_Renderer.Draw3D();
		m_Camera.EndCameraDraw();
		DrawFPS(10, 10);
		OnFrame();
		EndDrawing();
	}

	CloseWindow();
}

void Application::OnFrame()
{
	m_GUI.OnFrame();
	m_Renderer.Draw2D();
}
