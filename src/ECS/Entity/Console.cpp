#include "Console.h"
#include "../../ResourceManager.h"

Console::~Console()
{
	//m_Window->DeleteAllChildrens();
	std::cout << "[~Console] Deconstructing...\n";
}

void Console::Init()
{
	int width = GetScreenWidth() / 2;
	int	height = GetScreenHeight() / 2;
	int x = (GetScreenWidth() - width) / 2; 
	int y = (GetScreenHeight() - height) / 2;

	// Creating developer console 2d components
	m_TitleFont = ResourceManager::get().GetFontByName(TITLE_FONT);
	m_MessagesFont = ResourceManager::get().GetFontByName(MESSAGES_FONT);

	m_Window = ComponentsManager::get().Create2DComponent<ecs::Rectangle>(x, y, width, height, WINDOW_BG_COLOR);
	m_Window->SetDrawable(false);

	m_Topbar = ComponentsManager::get().Create2DComponent<ecs::Rectangle>(0, 0, width, 30, TOPBAR_BG_COLOR);
	m_Title = ComponentsManager::get().Create2DComponent<ecs::Text>(20, m_Topbar->height / 2 - m_TitleFontSize / 2, "Developer Console", m_TitleFontSize, FONT_COLOR, m_TitleFont, m_TextSpacing);
	m_CloseButton = ComponentsManager::get().Create2DComponent<ecs::Text>(m_Topbar->position.x + m_Topbar->width - m_TitleFontSize, m_Topbar->height / 2 - m_TitleFontSize / 2, "X", m_TitleFontSize, FONT_COLOR, m_TitleFont, m_TextSpacing);
	m_Input = ComponentsManager::get().Create2DComponent<ecs::Rectangle>(0, height - 30, width, 35, INPUT_BG_COLOR);
	m_InputText = ComponentsManager::get().Create2DComponent<ecs::Text>(10, m_Input->height / 2 - m_MessagesFontSize / 2, "", m_MessagesFontSize + 2, FONT_COLOR, m_MessagesFont, m_TextSpacing);

	m_ContentBox = ComponentsManager::get().Create2DComponent<ecs::Rectangle>(15, m_Topbar->height, width - 30, height - m_Input->height - m_Topbar->height, Color{100, 0, 0, 120});
	m_ContentBox->SetDrawable(false);
	m_ContentBox->SetExplicitLogic(true);

	ComponentsManager::get().AddComponentChildren(m_Window, m_Topbar);
	ComponentsManager::get().AddComponentChildren(m_Topbar, m_Title);
	ComponentsManager::get().AddComponentChildren(m_Topbar, m_CloseButton);
	ComponentsManager::get().AddComponentChildren(m_Window, m_Input);
	ComponentsManager::get().AddComponentChildren(m_Input, m_InputText);
	ComponentsManager::get().AddComponentChildren(m_Window, m_ContentBox);

	m_Window->SetName("[Console::Window]");
	m_Topbar->SetName("[Console::Topbar]");
	m_Title->SetName("[Console::Title]");
	m_CloseButton->SetName("[Console::CloseButton]");
	m_Input->SetName("[Console::Input]");
	m_InputText->SetName("[Console::InputText]");
	m_ContentBox->SetName("[Console::ContentBox]");

	CreateConsoleMessagesEntities();
}

void Console::OnFrame()
{
	// if window resized, resize the developer console too
	CheckWindowResize();

	// check if ` button has been pressed and toggle the rendering of the console
	CheckToggleShow();

	if (!m_Window->IsDrawable())
	{
		return;
	}

	CheckTopbarHover();
	CheckInputAction();
	CheckMouseScroll();

	if (m_IsTyping)
	{
		CheckInput();
	}

	SetCursorIcon();

	m_LastFrameMousePos = GetMousePosition();
}

void Console::RegisterCommand(const std::string& cmd, OnConsoleInputFnPtr func)
{
	m_OnConsoleInputFnPointers[cmd] = func;
	PushConsoleMessage(std::string("Registered console command ") + cmd, GREEN);
}

void Console::PushConsoleMessage(const std::string& text, const Color& color)
{
	//TODO: Add support for \n in console messages.
	CreateMessage(text, color);
}

void Console::ChangeTitleFontSize(int size)
{
	m_TitleFontSize = size;
}

void Console::ChangeMessagesFontSize(int size)
{
	m_MessagesFontSize = size;
}

void Console::CheckMessageDrawingByPos(std::shared_ptr<ecs::Text> message)
{
	if (message->GetAbsolutePosition().y < m_ContentBox->GetAbsolutePosition().y
		|| message->GetAbsolutePosition().y > m_ContentBox->GetAbsolutePosition().y + m_ContentBox->height
		|| message->GetAbsolutePosition().x < m_ContentBox->GetAbsolutePosition().x
		|| message->GetAbsolutePosition().x > m_ContentBox->GetAbsolutePosition().x + m_ContentBox->width
		)
	{
		message->SetDrawable(false);
		message->SetExplicitLogic(true);
	}
}

void Console::CreateConsoleMessagesEntities()
{
	if (m_MessagesComponentsMap.size() > 0)
	{
		for (std::shared_ptr<ecs::Text> messages : m_MessagesComponentsMap)
		{
			ComponentsManager::get().DeleteComponent(messages->GetID());
		}

		m_MessagesComponentsMap.clear();
	}

	float textHeight = MeasureTextEx((*m_MessagesFont.get()), "A", m_MessagesFontSize + 2, m_TextSpacing).y;
	unsigned short messagesCount = m_ContentBox->height / static_cast<int>(textHeight);

	for (unsigned short iter = 0; iter < messagesCount; iter++)
	{
		std::shared_ptr<ecs::Text> message = ComponentsManager::get().Create2DComponent<ecs::Text>(
			10, 0, "", m_MessagesFontSize + 2, FONT_COLOR, m_MessagesFont, m_TextSpacing
		);

		ComponentsManager::get().AddComponentChildren(m_ContentBox, message);
		message->position.y = m_ContentBox->height - ((iter + 1) * LINE_HEIGHT_MESSAGES) - ((iter + 1) * m_MessagesSpace);

		if (m_Messages.size() > 0 && iter < m_Messages.size())
		{
			message->text = (m_Messages.rbegin() + iter)->c_str();
		}
		else
		{
			message->text = "";
		}

		message->SetName("[Console::Message" + std::to_string(iter) + "]");
		message->SetDrawable(m_Window->IsDrawable());

		m_MessagesComponentsMap.push_back(message);
	}
}

void Console::CheckMouseScroll()
{
	if (!m_ContentBox->MouseHover())
	{
		return;
	}

	int totalMessages = m_Messages.size();
	int totalMessagesEntities = m_MessagesComponentsMap.size();

	if(totalMessages - 1 < totalMessagesEntities)
	{
		return;
	}
	
	float y = GetMouseWheelMove();

	if (y == 0.0f)
		return;

	if (totalMessagesEntities + m_CurrentMouseWheelY > totalMessages - 1 && y > 0.0f)
	{
		return;
	}

	m_CurrentMouseWheelY += y;

	if (m_CurrentMouseWheelY < 0)
	{
		m_CurrentMouseWheelY = 0;
	}

	if (m_CurrentMouseWheelY > totalMessages - 1)
	{
		m_CurrentMouseWheelY = totalMessages - 1;
	}

	for (std::size_t iter = 0; std::shared_ptr<ecs::Text> message : m_MessagesComponentsMap)
	{
		message->text = (m_Messages.rbegin() + m_CurrentMouseWheelY + iter++)->data();
	}
}

void Console::TriggerOnConsoleInputEvent(const std::string& text, const Color& color)
{
	auto whiteSpacePos = text.find(' ', 0);
	
	std::string command = "";

	if (whiteSpacePos == std::string::npos)
	{
		command = text;
	}
	else
	{
		command = text.substr(0, whiteSpacePos);
	}

	auto pair = m_OnConsoleInputFnPointers.find(command);
	if (pair != m_OnConsoleInputFnPointers.end())
	{
		pair->second(text);
	}
}

void Console::CreateMessage(const std::string& text, const Color& color)
{
	m_Messages.push_back(text);

	for (unsigned short iter = 0; std::shared_ptr<ecs::Text> message : m_MessagesComponentsMap)
	{
		if (iter < m_Messages.size())
		{
			message->text = (m_Messages.rbegin() + iter)->data();
		}
		else
		{
			break;
		}

		iter++;
	}
}

void Console::CheckInput()
{
	int key = GetKeyPressed();

	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && key != KEY_BACKSPACE && key != TOGGLE_CONSOLE_KEY)
		{
			if (!m_PressetCTRL)
			{
				m_InputText->text += GetCharPressed();
			}
			else if (m_PressetCTRL && key != KEY_A)
			{
				m_InputText->text.clear();
				m_PressetCTRL = false;
				m_SelectedInputText = false;
			}
		}
		else if (key == KEY_BACKSPACE)
		{
			if (m_InputText->text.size() > 0)
			{
				if (m_PressetCTRL)
				{
					m_InputText->text.clear();
					m_PressetCTRL = false;
					m_SelectedInputText = false;
				}
				else
				{
					m_InputText->text.pop_back();
				}
			}
		}
		else if (key == KEY_ENTER)
		{
			if (!m_InputText->text.size())
			{
				continue;
			}

			while (m_InputText->text[0] == KEY_SPACE)
			{
				m_InputText->text.erase(0, 1);
			}

			while (m_InputText->text.back() == KEY_SPACE)
			{
				m_InputText->text.pop_back();
			}

			CreateMessage(m_InputText->text, WHITE);
			TriggerOnConsoleInputEvent(m_InputText->text, WHITE);
			m_InputText->text.clear();
		}

		if (m_InputText->text.size() > 0)
		{
			if (key == KEY_LEFT_CONTROL || key == KEY_RIGHT_CONTROL)
			{
				m_PressetCTRL = true;
			}

			if (key == KEY_A)
			{
				if (m_PressetCTRL)
				{
					m_SelectedInputText = true;
				}
			}
		}

		key = GetCharPressed();
	}

	if (m_SelectedInputText)
	{
		DrawRectangle(
			m_InputText->GetAbsolutePosition().x - 2,
			m_InputText->GetAbsolutePosition().y - 2,
			MeasureText(m_InputText->text.c_str(), m_InputText->size) + 4,
			m_InputText->size + 4,
			{ 255, 255, 255, 60 }
		);
	}
}

void Console::CheckToggleShow()
{
	if (IsKeyPressed(TOGGLE_CONSOLE_KEY))
	{
		m_Window->SetDrawable(!m_Window->IsDrawable());

		if (m_Window->IsDrawable())
		{
			//m_Window->position.x = (GetScreenWidth() - m_Window->width) / 2.0;
			//m_Window->position.y = (GetScreenHeight() - m_Window->height) / 2.0;
			m_IsTyping = true;
			EnableCursor();
		}
		else
		{
			DisableCursor();
		}
	}
}

void Console::CheckWindowResize()
{
	if (IsWindowResized())
	{
		m_Window->width = GetScreenWidth() / 2;
		m_Window->height = GetScreenHeight() / 2;
		//m_Window->position.x = (GetScreenWidth() - m_Window->width) / 2.0;
		//m_Window->position.y = (GetScreenHeight() - m_Window->height) / 2.0;
		m_Topbar->width = m_Window->width;
		m_CloseButton->position.x = m_Topbar->position.x + m_Topbar->width - 20;
		m_Input->width = m_Window->width;
		m_Input->position.y = m_Window->height - m_Input->height;
		m_ContentBox->width = m_Window->width - 10;
		m_ContentBox->height = m_Window->height - m_Input->height - m_Topbar->height - 4;
		m_ContentBox->position.y = (m_Topbar->height + m_Input->height) / 2.0;
		m_ContentBox->position.x = 10.0 / 2.0 ;

		CreateConsoleMessagesEntities();
	}
}

void Console::CheckTopbarHover()
{
	if (m_Topbar->MouseHover())
	{
		m_Topbar->color = TOPBAR_HOVER_BG_COLOR;

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 newConsolePosition{};
			newConsolePosition.x = m_Window->position.x + (GetMousePosition().x - m_LastFrameMousePos.x);
			newConsolePosition.y = m_Window->position.y + (GetMousePosition().y - m_LastFrameMousePos.y);

			if (newConsolePosition.x + m_Window->width > 50 && newConsolePosition.x < GetScreenWidth() - 50
				&& newConsolePosition.y > 0 && newConsolePosition.y < GetScreenHeight() - m_Topbar->height)
			{
				m_Window->position.x = newConsolePosition.x;
				m_Window->position.y = newConsolePosition.y;
			}
		}
	}
	else
	{
		m_Topbar->color = TOPBAR_BG_COLOR;
	}

	if (m_CloseButton->MouseHover())
	{
		m_CloseButton->color = CLOSE_HOVER_COLOR;

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			m_Window->SetDrawable(false);
		}
	}
	else
	{
		m_CloseButton->color = FONT_COLOR;
	}
}


void Console::CheckInputAction()
{
	if (m_Input->MouseHover())
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			m_IsTyping = true;
		}
	}
	else
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			m_IsTyping = false;
			m_PressetCTRL = false;
			m_SelectedInputText = false;
		}
	}
}

void Console::SetCursorIcon()
{
	if (m_Input->MouseHover())
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
	}
	else if (!m_Topbar->MouseHover())
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}