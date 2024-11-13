#pragma once

#include "Component.h"

#include <vector>
#include <memory>
#include <cstdint>
#include <functional>
#include <string>
#include <iostream>

class Component;

class ComponentsManager
{
public:
	using ComponentsPtrMap = std::vector<std::shared_ptr<Component>>;
public:
	ComponentsManager() {};
	~ComponentsManager()
	{
		std::cout << "[~ComponentsManager] Destructing..\n";
		m_ComponentsMap.clear();
	};

	static ComponentsManager& get()
	{
		static ComponentsManager instance;
		return instance;
	}

	template<class ComponentType, typename ...Args>
	std::shared_ptr<ComponentType> CreateComponent(Args&& ...args)
	{
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>(std::forward<Args>(args)...);

		if (m_AvailableIDs.size())
		{
			std::size_t availableID = m_AvailableIDs.back();
			m_AvailableIDs.pop_back();

			component->SetID(availableID);
			m_ComponentsMap[availableID] = component;
		}
		else
		{
			m_ComponentsMap.push_back(component);
			component->SetID(m_ComponentsMap.size() - 1);
		}

		std::cout << "Created component with id " << component->GetID() << "\n";

		return component;
	}

	void DeleteComponent(const uint64_t index)
	{
		std::shared_ptr<Component> component = GetComponent<Component>(index);
		
		if (component == nullptr)
		{
			std::cerr << "Trying to delete invalid component with id " << index << "\n";
			return;
		}

		std::cout << "Deleting component " << component->GetName() << "\n";

		component->DeleteAllChildrens();

		for (std::shared_ptr<Component> children : component->GetChildrenComponents())
		{
			std::size_t childrenID = m_ComponentsMap[index]->GetID();
			m_ComponentsMap[childrenID].reset();
			m_AvailableIDs.push_back(childrenID);
		}

		if (component->GetParent())
		{
			component->GetParent()->DeleteChildren(component);
		}

		std::size_t componentID = m_ComponentsMap[index]->GetID();
		m_AvailableIDs.push_back(componentID);

		m_ComponentsMap[index].reset();
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> GetComponent(const uint64_t& index)
	{
		if (index >= m_ComponentsMap.size())
		{
			std::cerr << "Trying to get not existent component with id " << index << "\n";
			return nullptr;
		}

		return static_cast<std::shared_ptr<ComponentType>>(m_ComponentsMap[index]);
	}

	template<class ComponentType, class ChildrenType>
	void AddComponentChildren(std::shared_ptr<ComponentType> parent, std::shared_ptr<ChildrenType> child)
	{
		child->SetParent(parent);
		parent->AddChildren(child);
	}

	template<typename ComponentType>
	void DoForEachEntity(std::function<void(std::shared_ptr<ComponentType>)> func)
	{
		for (auto& componentPtr : m_ComponentsMap)
		{
			if (!componentPtr)
			{
				std::cerr << "Inexistent componentPtr " << __func__ << "::" << __LINE__ << "\n";
				continue;
			}

			std::shared_ptr<ComponentType> castedCompPtr = std::dynamic_pointer_cast<ComponentType>(componentPtr);

			if (!castedCompPtr)
			{
				continue;
			}

			func(castedCompPtr);
		}
	}

	ComponentsPtrMap& GetAllComponents()
	{
		return m_ComponentsMap;
	}

private:
	ComponentsPtrMap m_ComponentsMap;
	std::vector<std::size_t> m_AvailableIDs;
};