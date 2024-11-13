#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>

class ResourceManager
{
public:
	using ResourcesList = std::vector<std::string>;
public:
	const char* MAIN_RESOURCES_DIRECTORY = "assets";
	const char* FONTS_DIRECTORY = "fonts";
	const char* MODELS_DIRECTORY = "models";

public:
	~ResourceManager();
	static ResourceManager& get();

	std::shared_ptr<Font> PrecacheFont(const std::string& file);
	std::shared_ptr<Font> GetFontByName(const std::string& name);
	ResourcesList GetAvailableFonts();

	std::shared_ptr<Model> PrecacheModel(const std::string& file);
	std::shared_ptr<Model> GetModelByName(const std::string& name);
	ResourcesList GetAvailableModels();

	std::shared_ptr<Texture> PrecacheTexture(const std::string& file);

private:
	using FontsMap = std::unordered_map<std::string, std::shared_ptr<Font>>;
	using ModelsMap = std::unordered_map<std::string, std::shared_ptr<Model>>;
	using TexturesMap = std::unordered_map<std::string, std::shared_ptr<Texture>>;
private:
	std::optional<std::string> ResourceExists(const char* directory, const std::string& file);
	std::optional<std::string> GetFileName(const std::string& file);

private:
	FontsMap m_FontsMap;
	ModelsMap m_ModelsMap;
	TexturesMap m_TexturesMap;
};