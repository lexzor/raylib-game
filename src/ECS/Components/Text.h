#include "Base/DrawableComponent.h"
#include "raylib.h"

namespace ecs
{
	class Text : public DrawableComponent
	{
	public:
		Text() 
			: text("Text"), size(12), color{ 255, 0, 0, 255 }, font(nullptr), spacing(1.0f)
		{
		}

		Text(int x, int y, const std::string& text, int size, Color color, std::shared_ptr<Font> font = nullptr, float spacing = 1.0)
			: text(text), size(size), color(color), font(font), spacing(spacing)
		{
			Vector3* position = &this->GetTransform()->position;
			position->x = static_cast<float>(x);
			position->y = static_cast<float>(y);
			position->z = 0.0f;
		}

		~Text()
		{

		}

		void OnUpdate()
		{

		}
	
		void OnDraw()
		{
			if (!this->IsDrawable())
			{
				return;
			}

			if (this->GetParent())
			{
				std::shared_ptr<DrawableComponent> parentComponent = std::dynamic_pointer_cast<DrawableComponent>(this->GetParent());

				if (parentComponent)
				{
					std::shared_ptr<DrawableComponent> component = std::dynamic_pointer_cast<DrawableComponent>(this->GetParent());

					if (font != nullptr)
					{
						DrawTextEx(
							*(font.get()),
							text.c_str(),
							Vector2(
								this->GetTransform()->position.x + parentComponent->GetAbsolutePosition().position.x,
								this->GetTransform()->position.y + parentComponent->GetAbsolutePosition().position.y
							),
							size,
							spacing,
							color
						);
					}
					else
					{
						DrawText(
							text.c_str(),
							this->GetTransform()->position.x + parentComponent->GetAbsolutePosition().position.x,
							this->GetTransform()->position.y + parentComponent->GetAbsolutePosition().position.y,
							size,
							color
						);
					}
				}
			}
			else
			{
				if (font != nullptr)
				{
					DrawTextEx(
						*(font.get()),
						text.c_str(),
						Vector2(this->GetTransform()->position.x, this->GetTransform()->position.y),
						size,
						spacing,
						color
					);
				}
				else
				{
					DrawText(text.c_str(), this->GetTransform()->position.x, this->GetTransform()->position.y, size, color);
				}
			}
		}

		bool MouseHover()
		{
			const Vector2 mousePos = GetMousePosition();

			if (mousePos.x >= this->GetAbsolutePosition().position.x
				&& mousePos.x <= this->GetAbsolutePosition().position.x + MeasureText(text.c_str(), size)
				&& mousePos.y >= this->GetAbsolutePosition().position.y
				&& mousePos.y <= this->GetAbsolutePosition().position.y + size)
			{
				return true;
			}

			return false;
		}
	
		std::string ToString()
		{
			return std::string();
		}

		std::string text;
		int size;
		Color color;
		std::shared_ptr<Font> font;
		float spacing;
	};
}