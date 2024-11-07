#include "DeveloperConsole.h"

DeveloperConsole& DeveloperConsole::GetInstance()
{
	static DeveloperConsole instance;
	return instance;
}

void DeveloperConsole::SetConsole(std::shared_ptr<Console> console_ptr)
{
	m_Console = console_ptr;
}

void DeveloperConsole::PrintConsoleMessage(const std::string& text, const Color& color)
{
	m_Console->PushConsoleMessage(text, color);
}

void DeveloperConsole::RegisterConCommand(const std::string& cmd, Console::OnConsoleInputFnPtr fn)
{
	m_Console->RegisterCommand(cmd, fn);
}