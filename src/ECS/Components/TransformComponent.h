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

	std::string ToString() override
	{
		return std::string("x=") + std::to_string(position.x) + std::string(",y=") + std::to_string(position.y) + std::string(",z=") + std::to_string(position.z);
	}

	Vector3 position = {};
};