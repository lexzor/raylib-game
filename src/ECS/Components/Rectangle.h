#pragma once

#include "Base/DrawableComponent.h"

#include <iostream>
#include "raylib.h"

namespace ecs
{
	class Rectangle : public DrawableComponent
	{
	public:
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
			std::cout << "[~Rectangle] Deleting component " << this->GetName() << "\n";
		};
		
		void OnUpdate()
		{

		}

		std::string ToString() override
		{
			return std::string("Position: ") + this->GetTransform()->ToString() + std::string("\nWidth, Height: ") + std::to_string(width) + ", " + std::to_string(height);
		}

		void OnDraw()
		{
			if (this->GetParent())
			{
				std::shared_ptr<DrawableComponent> parentComponent  = std::dynamic_pointer_cast<DrawableComponent>(this->GetParent());
				
				if (parentComponent && parentComponent->IsDrawable())
				{
					std::shared_ptr<DrawableComponent> component = std::dynamic_pointer_cast<DrawableComponent>(this->GetParent());

					DrawRectangle(
						static_cast<int>(this->GetTransform()->position.x + parentComponent->GetTransform()->position.x),
						static_cast<int>(this->GetTransform()->position.y + parentComponent->GetTransform()->position.y),
						width,
						height,
						color
					);
				}
			}
			else
			{
				DrawRectangle(this->GetTransform()->position.x, this->GetTransform()->position.y, width, height, color);
			}
		}

		int width;
		int height;
		Color color;
	};
}