#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>
#include <memory>


class ResourceManager
{
public:
	const char* MAIN_RESOURCES_DIRECTORY = "assets";
	const char* FONTS_DIRECTORY = "fonts";

public:
	~ResourceManager();
	static ResourceManager& GetInstance();

	void PrecacheFont(const std::string& file_name);
	std::shared_ptr<Font> GetFontByName(const std::string& font_name);

private:
	std::unordered_map<std::string, std::shared_ptr<Font>> m_FontsMap;
};