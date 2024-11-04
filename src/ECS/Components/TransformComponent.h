#pragma once

#include "Base/Component.h"
#include "raylib.h"

class TransformComponent : public Component
{
public:
	TransformComponent()
		: position({0.0f, 0.0f, 0.0f})
	{
	}

	TransformComponent(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}
	~TransformComponent() {}

	void OnUpdate() override
	{

	}

	Vector3 position = {};
};