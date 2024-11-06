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

	//SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	ResourceManager::GetInstance().PrecacheFont("coolvetica_regular.otf");
	ResourceManager::GetInstance().PrecacheFont("bebas_neue_regular.otf");
	
	DeveloperConsole::GetInstance().InitConsole();
	DisableCursor();

	m_Commands.Init();
}

void Application::Run()
{
	CameraController3D cameraController{};

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground({ 0, 0, 0, 255 });
		DrawFPS(10, 10);

		cameraController.BeginCamera();
		DrawGrid(10, 1.0f); // Draw a grid for orientation
		DrawCube({ 0, 1, 0 }, 1, 1, 1, RED); // Sample object in the scene
		cameraController.OnUpdate();
		cameraController.EndCamera();

		OnFrame();
		EndDrawing();
	}

	CloseWindow();
}

void Application::OnFrame()
{
	DeveloperConsole::GetInstance().m_Console->OnFrame();
	m_Renderer.Draw();
}
