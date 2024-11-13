#pragma once

#include "Base/DrawableComponent.h"
#include "raylib.h"

namespace ecs
{
	class Model : public DrawableComponent
	{
	public:
		Model(std::shared_ptr<::Model> model)
			: model(model), rotationAxis({ 0, 0, 0 }), rotationAngle(0.0f), scale({ 0.1f, 0.1f, 0.1f }), tint({ 255,255,255,255 }) {}

		Model()
			: model(nullptr), rotationAxis({ 0, 0, 0 }), rotationAngle(0.0f), scale({ 0.0f, 0.0f, 0.0f }), tint({ 255,255,255,255 }) {}

		void OnUpdate()
		{

		}
		void OnDraw()
		{
			if (!model)
			{
				return;
			}

			DrawModelEx(*(model.get()), position, rotationAxis, rotationAngle, scale, tint);
		}

		std::string ToString()
		{
			return std::string();
		}

	public:
		Vector3 rotationAxis;
		float rotationAngle;
		Vector3 scale;
		Color tint;
		std::shared_ptr<::Model> model;
	};
}