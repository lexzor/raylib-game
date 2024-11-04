#pragma once

#include "Base/DrawableComponent.h"

#include <iostream>
#include "raylib.h"

namespace ecs
{
	class Rectangle : public DrawableComponent
	{
	public:
		Rectangle() : x(0), y(0), width(0), height(0), color{255,255,255,255} {}
		Rectangle(int x, int y, int width, int height, Color color)
			: x(x), y(y), width(width), height(height), color(color)
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
			std::cout << "OnDraw\n";
			DrawRectangle(x, y, width, height, color);
		}

		int x, y, width, height;
		Color color;
	};
}