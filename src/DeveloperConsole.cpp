#include "DeveloperConsole.h"

DeveloperConsole& DeveloperConsole::GetInstance()
{
	static DeveloperConsole instance;
	return instance;
}

void DeveloperConsole::InitConsole()
{
	m_Console = std::make_unique<Console>();
	m_Console->Init();
}

void DeveloperConsole::PrintConsoleMessage(const std::string& text, const Color& color)
{
	m_Console->PushConsoleMessage(text, color);
}

void DeveloperConsole::RegisterConCommand(const std::string& cmd, Console::OnConsoleInputFnPtr fn)
{
	m_Console->RegisterCommand(cmd, fn);
}