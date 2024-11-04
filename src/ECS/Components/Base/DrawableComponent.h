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
	virtual std::string ToString() = 0;
	virtual void OnDraw() = 0;

	void SetParentRelativeness(bool value) { m_IsRelativeToParent = value; }
	bool GetParentRelativeness() const { return m_IsRelativeToParent; }

	std::shared_ptr<TransformComponent> GetTransform()
	{
		return m_TransformComponent;
	}

private:
	bool m_IsRelativeToParent = false;
	std::shared_ptr<TransformComponent> m_TransformComponent ;
};