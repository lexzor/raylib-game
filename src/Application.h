#pragma once
#include "raylib.h"
#include "Renderer.h"
#include "ECS/Components/Rectangle.h"
#include "ECS/Entity/Console.h"

class Application
{
public:
	Application();
	~Application();
	
	void Init();
	void Run();

private:
	void OnFrame();

	Renderer m_Renderer;
	Console m_Console;
};