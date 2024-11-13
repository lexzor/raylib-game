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
	DevCon().RegisterConCommand("dc", [this](const std::string& input) {
		
		std::size_t components[2]{0};
		std::size_t highestID = 0;

		for (std::shared_ptr<Component> component : ComponentsManager::get().GetAllComponents())
		{
			if (component)
			{
				components[0]++;
				if (component->GetParent())
				{
					std::cout << "Valid Component " << component->GetID() << "." << component->GetName() << ", Parent: " << component->GetParent()->GetID() << "." << component->GetParent()->GetName() << "\n";
				}
				else
				{
					std::cout << "Valid Component " << component->GetID() << "." << component->GetName() << "\n";
				}
				highestID = std::max(component->GetID(), highestID);
			}
			else
			{
				components[1]++;
			}

		}

		conprint_g("There are  " + std::to_string(components[0]) + " available and " + std::to_string(components[1]) + " unavailable");
		conprint_g("highest id: " + std::to_string(highestID));
	});
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