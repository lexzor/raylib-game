#pragma once
#include "raylib.h"
#include "Renderer.h"
#include "ECS/Components/Rectangle.h"
#include "ECS/Entity/Console.h"
#include "ConsoleCommands.h"
#include "CameraController3D.h"

class Application
{
public:
	Application();
	~Application();
	
	void Init();
	void Run();

private:
	void OnFrame();

	Renderer m_Renderer = {};
	ConsoleCommands m_Commands = {};
	Camera m_Camera = {};
};