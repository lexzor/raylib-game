#pragma once

#include "Component.h"

class DrawableComponent : public Component
{
public:
	DrawableComponent()
	{
		SetDrawable(true);
	}

	virtual ~DrawableComponent() = default;
	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;
};