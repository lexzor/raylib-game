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
		}

		~Rectangle()
		{
		};
		
		void OnUpdate()
		{

		}

		void OnDraw()
		{
			if (this->GetParent() != nullptr)
			{
				if (this->GetParent()->IsDrawable())
				{
					std::shared_ptr<DrawableComponent> component = std::dynamic_pointer_cast<DrawableComponent>(this->GetParent());
				
					const TransformComponent* parentTransform = component->GetTransform();

					DrawRectangle(
						this->GetTransform()->position.x + parentTransform->position.x,
						this->GetTransform()->position.y + parentTransform->position.y,
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