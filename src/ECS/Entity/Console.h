#pragma once

// TODO: Absolute path
#include "../../ECS/Components/Base/ComponentsManager.h"
#include "../../ECS/Components/Rectangle.h"
#include "../../ECS/Components/Text.h"
#include <vector>
#include <unordered_map>
#include <functional>

constexpr unsigned char TOGGLE_CONSOLE_KEY			= 96;
constexpr Color WINDOW_BG_COLOR						= { 15, 15, 15, 255 };
constexpr Color WINDOW_BORDER_COLOR					= { 25, 25, 25, 255 };
constexpr Color TOPBAR_BG_COLOR						= { 35, 35, 35, 255 };
constexpr Color INPUT_BG_COLOR						= TOPBAR_BG_COLOR;
constexpr Color FONT_COLOR							= { 255, 255, 255, 255 };
constexpr Color TOPBAR_HOVER_BG_COLOR				= { 45, 45, 45, 255 };
constexpr Color CLOSE_HOVER_COLOR					= { 160, 160, 160, 255 };
constexpr unsigned short LINE_HEIGHT_MESSAGES		= 17;

constexpr const char* TITLE_FONT = "bebas_neue_regular";
constexpr const char* MESSAGES_FONT = "coolvetica_regular";

class Console
{
public:
	using OnConsoleInputFnPtr = std::function<void(const std::string&)>;
public:
	~Console();
	void Init();
	void OnFrame();

	void RegisterCommand(const std::string& cmd, OnConsoleInputFnPtr func);
	void PushConsoleMessage(const std::string& text, const Color& color);
	void ChangeTitleFontSize(int size);
	void ChangeMessagesFontSize(int size);

private:
	void CheckInput();
	void CheckToggleShow();
	void CheckWindowResize();
	void CheckTopbarHover();
	void CheckInputAction();
	void SetCursorIcon();
	void CreateMessage(const std::string& text, const Color& color);
	void TriggerOnConsoleInputEvent(const std::string& text, const Color& color);
	void CheckMessageDrawingByPos(std::shared_ptr<ecs::Text> message);

private:
	std::shared_ptr<ecs::Rectangle> m_Window = nullptr;
	std::shared_ptr<ecs::Rectangle> m_Topbar = nullptr;
	std::shared_ptr<ecs::Text> m_Title = nullptr;
	std::shared_ptr<ecs::Text> m_CloseButton = nullptr;
	std::shared_ptr<ecs::Text> m_InputText = nullptr;
	std::shared_ptr<ecs::Rectangle> m_Input = nullptr;
	std::shared_ptr<ecs::Rectangle> m_ContentBox = nullptr;

	std::shared_ptr<Font> m_TitleFont = nullptr;
	std::shared_ptr<Font> m_MessagesFont = nullptr;
	int m_TitleFontSize = 25;
	int m_MessagesFontSize = 19;
	float m_TextSpacing = 1.3f;

	bool m_IsTyping = false;
	bool m_PressetCTRL = false;
	bool m_SelectedInputText = false;
	bool m_NewMessage = false;
	Vector2 m_LastFrameMousePos = { 0.0, 0.0 };

	std::vector<std::string> m_Messages;
	std::vector<std::shared_ptr<ecs::Text>> m_MessagesComponentsMap;
	std::unordered_map<std::string, OnConsoleInputFnPtr> m_OnConsoleInputFnPointers;
};