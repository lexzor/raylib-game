#include "ResourceManager.h"
#include <iostream>
#include <filesystem>

ResourceManager::~ResourceManager()
{
    for (auto& map_pair : m_FontsMap)
    {
        UnloadFont(*(map_pair.second));
    }

    for (auto& map_pair : m_ModelsMap)
    {
        UnloadModel(*(map_pair.second));
    }
}

ResourceManager& ResourceManager::get()
{
    static ResourceManager instance;
    return instance;
}

std::shared_ptr<Font> ResourceManager::PrecacheFont(const std::string& file)
{
    const std::optional<std::string> path = ResourceExists(FONTS_DIRECTORY, file);
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

std::shared_ptr<Font> ResourceManager::GetFontByName(const std::string& name)
{
    if (m_FontsMap.find(name) == m_FontsMap.end())
    {
        std::cerr << "Failed to get model with name '" << name << "'\n";
        return nullptr;
    }

    return m_FontsMap[name];
}

ResourceManager::ResourcesList ResourceManager::GetAvailableFonts()
{
    if (m_FontsMap.size())
    {
        ResourcesList fonts = ResourcesList(m_FontsMap.size());
        for (std::size_t iter = 0; const auto& pair : m_FontsMap)
        {
            fonts[iter++] = pair.first;
        }

        return fonts;
    }

    return ResourcesList();
}

std::shared_ptr<Model> ResourceManager::PrecacheModel(const std::string& file)
{
    const std::optional<std::string> path = ResourceExists(MODELS_DIRECTORY, file);
    if (!path.has_value())
    {
        std::cerr << "Failed to find model '" << file << "'\n";
        return nullptr;
    }

    const std::optional<std::string> name = GetFileName(file);
    if (!name.has_value())
    {
        std::cerr << "Failed to get file name of model '" << file << "' (extension checking failed).\n";
        return nullptr;
    }

    Model model = LoadModel(path.value().c_str());
    if (model.meshCount == 0)
    {
        std::cerr << "Failed to load model '" << file << "'\n";
        return nullptr;
    }
  
    m_ModelsMap[name.value()] = std::move(std::make_shared<Model>(model));
    return m_ModelsMap[name.value()];
}

std::shared_ptr<Model> ResourceManager::GetModelByName(const std::string& name)
{
    if (m_ModelsMap.find(name) == m_ModelsMap.end())
    {
        std::cerr << "Failed to get model with name '" << name << "'\n";
        return nullptr;
    }

    return m_ModelsMap[name];
}

ResourceManager::ResourcesList ResourceManager::GetAvailableModels()
{
    if (m_ModelsMap.size())
    {
        ResourcesList models(m_ModelsMap.size());

        for (std::size_t iter = 0; const auto & pair : m_ModelsMap)
        {
            models[iter++] = pair.first;
        }

        return models;
    }

    return ResourcesList();
}

std::shared_ptr<Texture> ResourceManager::PrecacheTexture(const std::string& file)
{
    const std::optional<std::string> path = ResourceExists(MODELS_DIRECTORY, file);
    if (!path.has_value())
    {
        std::cerr << "Failed to find texture '" << file << "'\n";
        return nullptr;
    }

    const std::optional<std::string> name = GetFileName(file);
    if (!name.has_value())
    {
        std::cerr << "Failed to get file name of texture '" << file << "' (extension checking failed).\n";
        return nullptr;
    }

    Texture texture = LoadTexture(path.value().c_str());
    if (texture.id == 0)
    {
        std::cerr << "Failed to load texture '" << file << "'\n";
        return nullptr;
    }

    m_TexturesMap[name.value()] = std::move(std::make_shared<Texture>(texture));
    return m_TexturesMap[name.value()];
}

std::optional<std::string> ResourceManager::ResourceExists(const char* directory, const std::string& file)
{
    std::filesystem::path path = std::filesystem::current_path() / MAIN_RESOURCES_DIRECTORY / directory / file;

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
