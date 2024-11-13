#pragma once
#include "ECS/Entity/Console.h"
#include "raylib.h"
#include <string>
#include <memory>

#define DevCon() DeveloperConsole::get()

#define conprint(message) DeveloperConsole::get().PrintConsoleMessage(message, WHITE)
#define conprint_r(message) DeveloperConsole::get().PrintConsoleMessage(message, RED)
#define conprint_y(message) DeveloperConsole::get().PrintConsoleMessage(message, YELLOW)
#define conprint_g(message) DeveloperConsole::get().PrintConsoleMessage(message, GREEN)

class DeveloperConsole
{
public:
	static DeveloperConsole& get();

	void SetConsole(std::shared_ptr<Console> console_ptr);
	void PrintConsoleMessage(const std::string& text, const Color& color = WHITE);
	void RegisterConCommand(const std::string& cmd, Console::OnConsoleInputFnPtr fn);

private:
	std::shared_ptr<Console> m_Console = nullptr;
};