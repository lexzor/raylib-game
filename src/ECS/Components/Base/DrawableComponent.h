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
		m_TransformComponent = ComponentsManager::GetInstance().CreateComponent<TransformComponent>();
		m_TransformComponent->SetName("DrawableTransformComponent");
	}

	virtual ~DrawableComponent() = default;
	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;
	virtual std::string ToString() = 0;

	TransformComponent GetAbsolutePosition()
	{
		if (this->GetParent())
		{
			std::shared_ptr<DrawableComponent> parentComponent = std::dynamic_pointer_cast<DrawableComponent>(this->GetParent());

			if (parentComponent)
			{	
				TransformComponent component{};
				component.position.x = parentComponent->GetAbsolutePosition().position.x + m_TransformComponent->position.x;
				component.position.y = parentComponent->GetAbsolutePosition().position.y + m_TransformComponent->position.y;
				component.position.z = parentComponent->GetAbsolutePosition().position.z + m_TransformComponent->position.z;
				
				return component;
			}

			return { m_TransformComponent->position.x, m_TransformComponent->position.y, m_TransformComponent->position.z };
		}

		//std::cout << "returned local position\n";

		return { m_TransformComponent->position.x, m_TransformComponent->position.y, m_TransformComponent->position.z };
	}

	std::shared_ptr<TransformComponent> GetTransform()
	{
		return m_TransformComponent;
	}

private:
	std::shared_ptr<TransformComponent> m_TransformComponent ;
};