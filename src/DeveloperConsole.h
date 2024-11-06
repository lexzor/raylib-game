#pragma once
#include "ECS/Entity/Console.h"
#include "raylib.h"
#include <string>
#include <memory>

#define DevCon() DeveloperConsole::GetInstance()

#define conprint(message) DeveloperConsole::GetInstance().PrintConsoleMessage(message, WHITE)
#define conprint_r(message) DeveloperConsole::GetInstance().PrintConsoleMessage(message, RED)
#define conprint_y(message) DeveloperConsole::GetInstance().PrintConsoleMessage(message, YELLOW)
#define conprint_g(message) DeveloperConsole::GetInstance().PrintConsoleMessage(message, GREEN)

class DeveloperConsole
{
	friend class Application;
public:
	static DeveloperConsole& GetInstance();

	void InitConsole();
	void PrintConsoleMessage(const std::string& text, const Color& color = WHITE);
	void RegisterConCommand(const std::string& cmd, Console::OnConsoleInputFnPtr fn);

private:
	std::unique_ptr<Console> m_Console = nullptr;
};