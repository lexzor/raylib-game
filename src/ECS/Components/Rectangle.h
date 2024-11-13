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
			Vector3* position = &this->position;
			position->x = static_cast<float>(x);
			position->y = static_cast<float>(y);
			position->z = 0.0f;
		}
		
		~Rectangle()
		{
		}

		void OnUpdate()
		{
		}

		std::string ToString() override
		{
			return std::string("ToString not implemented for Rectangle");
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
						static_cast<int>(this->GetAbsolutePosition().x),
						static_cast<int>(this->GetAbsolutePosition().y),
						width,
						height,
						color
					);
				}
			}
			else
			{
				DrawRectangle(this->position.x, this->position.y, width, height, color);
			}
		}

		bool MouseHover()
		{
			const Vector2 mousePos = GetMousePosition();
		
			if (mousePos.x >= this->GetAbsolutePosition().x
				&& mousePos.x <= this->GetAbsolutePosition().x + width
				&& mousePos.y >= this->GetAbsolutePosition().y
				&& mousePos.y <= this->GetAbsolutePosition().y + height)
			{
				return true;
			}

			return false;
		}

		int width;
		int height;
		Color color;
	};
}