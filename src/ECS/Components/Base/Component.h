#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

class Component
{
public:
	//virtual ~Component() { std::cout << "[~Component] deleting component " << this->GetName() << "\n"; };
	virtual ~Component() = default;
	virtual void OnUpdate() = 0;
	virtual std::string ToString() = 0;

	void SetName(const std::string& name) { m_Name = name; }
	const std::string& GetName() { return m_Name; }

	// Explicit logic components can't be drawn to the screen, it's used only for screen positioning
	void SetExplicitLogic(bool value) { m_ExplicitLogicComponent = value; m_Drawable = false; }
	bool GetExplicitLogic() const { return m_ExplicitLogicComponent; }

	void SetDrawable(bool value)
	{
		// We can't change the drawable value after the component has been set as a logic component, but we can change it's child drawable value
		if (m_ChildrenComponents.size() > 0)
		{
			for (std::shared_ptr<Component> child : m_ChildrenComponents)
			{
				child->SetDrawable(value);
			}
		}
		
		if (GetExplicitLogic())
		{
			return;
		}

		m_Drawable = value;
	}
	bool IsDrawable() const { return m_Drawable; }

	void SetID(const uint64_t& id) { m_ComponentID = id; }
	const uint64_t GetID() const { return m_ComponentID; }

	std::shared_ptr<Component> GetParent() { return m_ParentComponent; }
	virtual void SetParent(std::shared_ptr<Component> parent)
	{
		m_ParentComponent = parent;
	}

	void SetParentRelativeness(bool value) { m_IsRelativeToParent = value; }
	bool GetParentRelativeness() const { return m_IsRelativeToParent; }

	std::vector<std::shared_ptr<Component>>& GetChildrenComponents()
	{
		return m_ChildrenComponents;
	}

	void AddChildren(std::shared_ptr<Component> component)
	{
		component->SetDrawable(IsDrawable());
		m_ChildrenComponents.push_back(component);
	}

	void DeleteChildren(std::shared_ptr<Component> component)
	{
		std::vector<std::shared_ptr<Component> >::iterator children = std::find(m_ChildrenComponents.begin(), m_ChildrenComponents.end(), component);

		if (children != m_ChildrenComponents.end())
		{
			m_ChildrenComponents.erase(children);
			return;
		}

		std::cerr << "Trying to remove a children from parent component "
			<< this->GetName().data()
			<< " which does not exists. Children name: "
			<< component->GetName()
			<< "\n";
	}

	void DeleteAllChildrens()
	{
		m_ChildrenComponents.clear();
	}

private:
	bool m_Drawable = false;
	bool m_ExplicitLogicComponent = false;
	bool m_IsRelativeToParent = true;
	std::shared_ptr<Component> m_ParentComponent = nullptr;
	std::vector<std::shared_ptr<Component>> m_ChildrenComponents;
	std::string m_Name = "NameNotSet";
	uint64_t m_ComponentID;
};