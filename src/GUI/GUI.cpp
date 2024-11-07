#include "GUI.h"

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::Init()
{
	m_Console = std::make_shared<Console>();
	m_Console->Init();
}

void GUI::OnFrame()
{
	m_Console->OnFrame();
}

std::shared_ptr<Console> GUI::GetConsole()
{
	return m_Console;
}
