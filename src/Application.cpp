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
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	InitWindow(1300, 800, "TagME!");
	DisableCursor();

	//SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	ResourceManager::get().PrecacheFont("coolvetica_regular.otf");
	ResourceManager::get().PrecacheFont("bebas_neue_regular.otf");

	m_GUI.Init();
	DeveloperConsole::get().SetConsole(m_GUI.GetConsole());

	m_Commands.Init();
}

void Application::Run()
{
	std::shared_ptr<Model> lion = ResourceManager::get().PrecacheModel("map/scene.gltf");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground({ 0, 0, 0, 255 });
		m_Camera.BeginCameraDraw();
		DrawGrid(20, 1.0f); // Draw a grid for orientation
		//DrawCube({ 0, 1, 0 }, 1, 1, 1, RED); // Sample object in the scene
		
		//DrawModel(*(cat.get()), { 0, 1, 0 }, 0.1, { 255,255,255,255 });`
		//DrawModelEx(*(lion.get()), { 0, 1, 0 }, {1, 1, 1}, 180.0f, {1.0f, 1.0f, 1.0f}, {255,255,255,255});
		DrawCube({ 0, 0.1, 0 }, 500.0, 0.2, 500.0, { 35, 109, 0, 255 });

		m_Camera.OnFrame();
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
	m_Renderer.Draw();
}
