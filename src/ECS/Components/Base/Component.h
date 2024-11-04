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

	void SetDrawable(bool value)
	{
		m_Drawable = value;
		if (m_ChildrenComponents.size() > 0)
		{
			for (std::shared_ptr<Component> child : m_ChildrenComponents)
			{
				child->SetDrawable(value);
			}
		}
	}
	bool IsDrawable() const { return m_Drawable; }

	void SetID(const uint64_t& id) { m_ComponentID = id; }
	const uint64_t GetID() const { return m_ComponentID; }

	std::shared_ptr<Component> GetParent() { return m_ParentComponent; }

	virtual void SetParent(std::shared_ptr<Component> parent)
	{
		m_ParentComponent = parent;
	}

	std::vector<std::shared_ptr<Component>>& GetChildrenComponents()
	{
		return m_ChildrenComponents;
	}

	void AddChildren(std::shared_ptr<Component> component)
	{
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
	std::shared_ptr<Component> m_ParentComponent = nullptr;
	std::vector<std::shared_ptr<Component>> m_ChildrenComponents;
	std::string m_Name = "NameNotSet";
	uint64_t m_ComponentID;
};