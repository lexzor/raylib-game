#pragma once

#include "Base/Component.h"
#include "raylib.h"

class TransformComponent : public Component
{
	Vector3 position = {};
};