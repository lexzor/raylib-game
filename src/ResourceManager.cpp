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

std::shared_ptr<Font> ResourceManager::PrecacheFont(const std::string& file)
{
    const std::optional<std::string> path = ResourceExists(file);
    if (!path.has_value())
    {
        std::cerr << "Failed to find font '" << file << "'\n";
        return nullptr;
    }

    const std::optional<std::string> name = GetFileName(file);
    if (!name.has_value())
    {
        std::cerr << "Failed to get file name of font '" << file << "' (extension checking failed).\n";
        return nullptr;
    }

    Font font = LoadFont(path.value().c_str());
    if (font.texture.id == 0)
    {
        std::cerr << "Failed to load font '" << file << "'\n";
        return nullptr;
    }
    
    m_FontsMap[name.value()] = std::move(std::make_shared<Font>(font));
    return m_FontsMap[name.value()];
}

std::shared_ptr<Font> ResourceManager::GetFontByName(const std::string& font)
{
    if (m_FontsMap.find(font) == m_FontsMap.end())
    {
        std::cerr << "Failed to get font with name '" << font << "'\n";
        return nullptr;
    }

    return m_FontsMap[font];
}

std::vector<std::string> ResourceManager::GetAvailableFonts()
{
    std::vector<std::string> fonts;
    fonts.resize(m_FontsMap.size());

    for (std::size_t iter = 0; const auto& pair : m_FontsMap)
    {
        fonts[iter++] = pair.first;
    }

    return fonts;
}

std::optional<std::string> ResourceManager::ResourceExists(const std::string& file)
{
    std::filesystem::path path = std::filesystem::current_path() / MAIN_RESOURCES_DIRECTORY / FONTS_DIRECTORY / file;

    if (!std::filesystem::exists(path))
    {
        std::cerr << "Font could not be found. Full path: " << path << "\n";
        return std::nullopt;
    }

    return std::optional<std::string>{ path.string() };
}

std::optional<std::string> ResourceManager::GetFileName(const std::string& file)
{
    const auto& pos = file.find('.');
    if (pos == std::string::npos)
    {
        std::cerr << "Failed to find extension for font '" << file << "'\n";
        return std::nullopt;
    }

    return std::optional<std::string>(file.substr(0, pos));
}
