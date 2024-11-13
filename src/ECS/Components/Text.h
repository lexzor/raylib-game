#pragma once

#include "Base/DrawableComponent.h"
#include "raylib.h"

namespace ecs
{
	class Text : public DrawableComponent
	{
	public:
		Text() 
			: text("Text"), size(12), color{ 255, 0, 0, 255 }, font(nullptr), spacing(1.0f), draw_borders(false), border_color({ 255,0,0,255 })
		{
		}

		Text(int x, int y, const std::string& text, int size, Color color, std::shared_ptr<Font> font = nullptr, float spacing = 1.0, bool draw_borders = false, Color border_color = {255,255,255,255})
			: text(text), size(size), color(color), font(font), spacing(spacing), draw_borders(draw_borders), border_color(color)
		{
			Vector3* position = &this->position;
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
					Vector2 absolutePosition{ 0 };
					absolutePosition.x = this->position.x + parentComponent->GetAbsolutePosition().x;
					absolutePosition.y = this->position.y + parentComponent->GetAbsolutePosition().y;
					
					if (font != nullptr)
					{	
						DrawTextEx(
							*(font.get()),
							text.c_str(),
							absolutePosition,
							size,
							spacing,
							color
						);
					}
					else
					{
						DrawText(
							text.c_str(),
							absolutePosition.x,
							absolutePosition.y,
							size,
							color
						);
					}

					if (ShouldDrawBorder())
					{
						Vector2 sizes = MeasureTextEx((*font.get()), text.c_str(), size, spacing);
						DrawRectangleLines(absolutePosition.x, absolutePosition.y, sizes.x, sizes.y, border_color);
					}
				}
				else
				{
					std::cerr << "Component " << this->GetID() << "." << this->GetName() << " can't be drawn because parent it's invalid\n";
				}
			}
			else
			{
				if (font)
				{
					DrawTextEx(
						*(font.get()),
						text.c_str(),
						Vector2(this->position.x, this->position.y),
						size,
						spacing,
						color
					);
				}
				else
				{
					DrawText(text.c_str(), this->position.x, this->position.y, size, color);
				}

				if (ShouldDrawBorder())
				{
					Vector2 sizes = MeasureTextEx((*font.get()), text.c_str(), size, spacing);
					DrawRectangleLines(this->position.x, this->position.y, sizes.x, sizes.y, border_color);
				}
			}
		}

		bool MouseHover()
		{
			const Vector2 mousePos = GetMousePosition();

			if (mousePos.x >= this->GetAbsolutePosition().x
				&& mousePos.x <= this->GetAbsolutePosition().x + MeasureText(text.c_str(), size)
				&& mousePos.y >= this->GetAbsolutePosition().y
				&& mousePos.y <= this->GetAbsolutePosition().y + size)
			{
				return true;
			}

			return false;
		}

		bool ShouldDrawBorder() const { return draw_borders; }
	
		std::string ToString()
		{
			return std::string();
		}

		std::string text;
		int size;
		Color color;
		std::shared_ptr<Font> font;
		float spacing;
		bool draw_borders;
		Color border_color;
	};
}