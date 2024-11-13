#pragma once

#include "Component.h"
#include "../TransformComponent.h"
#include "ComponentsManager.h"

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
	virtual std::string ToString() = 0;

	Vector3 GetAbsolutePosition()
	{
		if (this->GetParent())
		{
			std::shared_ptr<DrawableComponent> parentComponent = std::dynamic_pointer_cast<DrawableComponent>(this->GetParent());

			if (parentComponent)
			{	
				return Vector3({
					.x = parentComponent->GetAbsolutePosition().x + position.x,
					.y = parentComponent->GetAbsolutePosition().y + position.y,
					.z = parentComponent->GetAbsolutePosition().z + position.z,
				});
			}

			return Vector3{ position.x, position.y, position.z };
		}

		return Vector3{ position.x, position.y, position.z };
	}

	bool ShouldDrawBorder() const { return m_DrawBorders; }
	void SetBordersDrawing(bool value) { m_DrawBorders = value; }

public:
	Vector3 position{0};
	Color border_color = { 255, 255, 255, 255 };

private:
	bool m_DrawBorders = false;
};