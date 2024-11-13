#include "ConsoleCommands.h"
#include "ResourceManager.h"

ConsoleCommands::ConsoleCommands()
{
}

ConsoleCommands::~ConsoleCommands()
{
}

void ConsoleCommands::Init()
{
	DevCon().RegisterConCommand("print_fonts", [this](const std::string& input) { this->PrintFonts(input); });
}

void ConsoleCommands::PrintFonts(const std::string& input)
{
	ResourceManager::ResourcesList fontsList = ResourceManager::get().GetAvailableFonts();

	conprint_g("Total available fonts: " + std::to_string(fontsList.size()));

	for (std::size_t iter = 0; std::string& font : fontsList)
	{
		conprint(std::to_string(iter++) + ". " + font);
	}
}