#include "Application.h"

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

	m_Console.Init();
}

void Application::Run()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground({ 255, 255, 255, 255 });
		OnFrame();
		EndDrawing();
	}
}

void Application::OnFrame()
{
	m_Renderer.Draw();
}
