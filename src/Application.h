#pragma once
#include "raylib.h"
#include "Renderer.h"
#include "ECS/Components/Rectangle.h"

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
	std::shared_ptr<ecs::Rectangle> m_Rectangle;
};