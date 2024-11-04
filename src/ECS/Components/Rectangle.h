#include "Base/DrawableComponent.h"

#include <iostream>
#include "raylib.h"

namespace ecs
{
	class Rectangle : public DrawableComponent
	{
	public:
		Rectangle() = delete;
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