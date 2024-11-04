#include "ResourceManager.h"
#include <iostream>
#include <filesystem>

ResourceManager::~ResourceManager()
{
    for (auto& map_pair : m_FontsMap)
    {
        UnloadFont(*(map_pair.second));
    }
}

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

void ResourceManager::PrecacheFont(const std::string& file_name)
{
    std::filesystem::path path = std::filesystem::current_path() / MAIN_RESOURCES_DIRECTORY / FONTS_DIRECTORY / file_name;

    if (!std::filesystem::exists(path))
    {
        std::cerr << "Font could not be found. Full path: " << path << "\n";
        return;
    }

    const auto& pos = file_name.find('.');
    if (pos == std::string::npos)
    {
        std::cerr << "Failed to find extension for font '" << file_name << "'\n";
        return;
    }

    std::cout << "Succesfully loaded font '" << file_name << "'\n";

    //std::cout << "File full path: " << path << "\n";
    std::cout << "Raylib working directory: " << GetWorkingDirectory() << "\n";
    std::cout << "Raylib application directory: " << GetApplicationDirectory() << "\n";
    
    m_FontsMap[file_name.substr(0, pos)] = std::make_shared<Font>(LoadFont(path.string().c_str()));
}

std::shared_ptr<Font> ResourceManager::GetFontByName(const std::string& font_name)
{
    if (m_FontsMap.find(font_name) == m_FontsMap.end())
    {
        std::cerr << "Failed to get font with name '" << font_name << "'\n";
        return nullptr;
    }

    return m_FontsMap[font_name];
}
