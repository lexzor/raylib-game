#pragma once
#include "raylib.h"
#include "Renderer.h"
#include "ECS/Components/Rectangle.h"
#include "ECS/Entity/Console.h"
#include "ConsoleCommands.h"
#include "GUI/GUI.h"
#include "CameraController.h"
#include "EntityCreator.h"

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
	CameraController m_Camera = {};
	GUI m_GUI = {};

	EntityCreator m_EntityCreator = {};
};