#pragma once

#include "Base/DrawableComponent.h"

#include <iostream>
#include "raylib.h"

namespace ecs
{
	class Rectangle : public DrawableComponent
	{
	public:

		// TODO: Create multiple constructors
		Rectangle() : width(0), height(0), color{255,255,255,255} {}

		Rectangle(int x, int y, int width, int height, Color color)
			: width(width), height(height), color(color)
		{
			Vector3* position = &this->GetTransform()->position;
			position->x = static_cast<float>(x);
			position->y = static_cast<float>(y);
			position->z = 0.0f;
		}

		~Rectangle()
		{
		};
		
		bool GetBordersDrawing() const { return m_DrawBorders; }
		void SetBordersDrawing(bool value) { m_DrawBorders = value; }

		void OnUpdate()
		{
		}

		std::string ToString() override
		{
			return std::string("Position: ") + this->GetTransform()->ToString() + std::string("\nWidth, Height: ") + std::to_string(width) + ", " + std::to_string(height);
		}

		void OnDraw()
		{
			if (!this->IsDrawable())
			{
				return;
			}

			if (this->GetParent() && this->GetParentRelativeness())
			{
				std::shared_ptr<DrawableComponent> parentComponent  = std::dynamic_pointer_cast<DrawableComponent>(this->GetParent());
				
				if (parentComponent)
				{
					DrawRectangle(
						static_cast<int>(this->GetAbsolutePosition().position.x),
						static_cast<int>(this->GetAbsolutePosition().position.y),
						width,
						height,
						color
					);

					//TODO: Implement border drawing, each childs of the component should automatically calculate their position and size

					//if (m_DrawBorders)
					//{
					//	DrawRectangleLinesEx({
					//		.x = this->GetTransform()->position.x + parentComponent->GetAbsolutePosition().position.x - border_thickness,
					//		.y = this->GetTransform()->position.y + parentComponent->GetAbsolutePosition().position.y - border_thickness,
					//		.width = static_cast<float>(width) + border_thickness,
					//		.height = static_cast<float>(height) + border_thickness
					//	}, 
					//		border_thickness, border_color);
					//}
				}
			}
			else
			{
				DrawRectangle(this->GetTransform()->position.x, this->GetTransform()->position.y, width, height, color);

				//if (m_DrawBorders)
				//{
				//	DrawRectangleLinesEx({
				//		.x = this->GetTransform()->position.x - border_thickness,
				//		.y = this->GetTransform()->position.y - border_thickness,
				//		.width = static_cast<float>(width) + border_thickness,
				//		.height = static_cast<float>(height) + border_thickness
				//		},
				//		border_thickness, border_color);
				//}
			}
		}

		bool MouseHover()
		{
			const Vector2 mousePos = GetMousePosition();
		
			if (mousePos.x >= this->GetAbsolutePosition().position.x
				&& mousePos.x <= this->GetAbsolutePosition().position.x + width
				&& mousePos.y >= this->GetAbsolutePosition().position.y
				&& mousePos.y <= this->GetAbsolutePosition().position.y + height)
			{
				return true;
			}

			return false;
		}

		int width;
		int height;
		Color color;

	private:
		bool m_DrawBorders = false;
	};
}