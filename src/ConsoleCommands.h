#pragma once

#include "DeveloperConsole.h"

class ConsoleCommands
{
public:
	ConsoleCommands();
	~ConsoleCommands();

	void Init();

private:
	void PrintFonts(const std::string& input);
};