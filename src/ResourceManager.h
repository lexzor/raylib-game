#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>

class ResourceManager
{
public:
	using ResourceList = std::vector<std::string>;
public:
	const char* MAIN_RESOURCES_DIRECTORY = "assets";
	const char* FONTS_DIRECTORY = "fonts";

public:
	~ResourceManager();
	static ResourceManager& GetInstance();

	std::shared_ptr<Font> PrecacheFont(const std::string& file);
	std::shared_ptr<Font> GetFontByName(const std::string& font);
	ResourceList GetAvailableFonts();

private:
	using FontsMap = std::unordered_map<std::string, std::shared_ptr<Font>>;
private:
	std::optional<std::string> ResourceExists(const std::string& file);
	std::optional<std::string> GetFileName(const std::string& file);

private:
	FontsMap m_FontsMap;
};