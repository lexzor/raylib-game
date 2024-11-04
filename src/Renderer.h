#pragma once

#include "ECS/Components/Base/ComponentsManager.h"
#include "ECS/Components/Base/DrawableComponent.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw();
};