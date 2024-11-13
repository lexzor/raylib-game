#pragma once

#include "Component.h"

#include <vector>
#include <memory>
#include <cstdint>
#include <functional>
#include <string>
#include <iostream>

class Component;

enum class ComponentDimension : uint8_t
{
	TwoD = 0,
	ThreeD = 1
};

class ComponentsManager
{
public:
	using ComponentsPtrMap = std::vector<std::shared_ptr<Component>>;
	using AvailableIDsVec = std::vector<uint64_t>;

	template<typename ComponentType>
	using Function = std::function<void(std::shared_ptr<ComponentType>)>;
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
	std::shared_ptr<ComponentType> Create2DComponent(Args&& ...args)
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

		return component;
	}

	template<class ComponentType, typename ...Args>
	std::shared_ptr<ComponentType> Create3DComponent(Args&& ...args)
	{
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>(std::forward<Args>(args)...);

		if (m_AvailableIDs.size())
		{
			std::size_t availableID = m_3DAvailableIDs.back();
			m_3DAvailableIDs.pop_back();

			component->SetID(availableID);
			m_3DComponentsMap[availableID] = component;
		}
		else
		{
			m_3DComponentsMap.push_back(component);
			component->SetID(m_3DComponentsMap.size() - 1);
		}

		return component;
	}

	void DeleteComponent(const ComponentDimension type, const uint64_t index)
	{
		std::shared_ptr<Component> component = GetComponent<Component>(type, index);
		
		if (component == nullptr)
		{
			std::cerr << "Trying to delete invalid component with id " << index << "\n";
			return;
		}

		ComponentsPtrMap* map = nullptr;
		AvailableIDsVec* vec = nullptr;

		if (type == ComponentDimension::TwoD)
		{
			map = &m_ComponentsMap;
			vec = &m_AvailableIDs;
		}
		else
		{
			map = &m_3DComponentsMap;
			vec = &m_3DAvailableIDs;
		}

		component->DeleteAllChildrens();

		for (std::shared_ptr<Component> children : component->GetChildrenComponents())
		{
			std::size_t childrenID = map->at(index)->GetID();
			map->at(childrenID).reset();
			vec->push_back(childrenID);
		}

		if (component->GetParent())
		{
			component->GetParent()->DeleteChildren(component);
		}

		std::size_t componentID = map->at(index)->GetID();
		vec->push_back(componentID);

		map->at(index).reset();
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> GetComponent(const ComponentDimension type, const uint64_t& index)
	{
		ComponentsPtrMap* map = nullptr;

		if (type == ComponentDimension::TwoD)
		{
			map = &m_ComponentsMap;
		}
		else
		{
			map = &m_3DComponentsMap;
		}

		if (index >= map->size())
		{
			std::cerr << "Trying to get not existent component with id " << index << "\n";
			return nullptr;
		}

		return static_cast<std::shared_ptr<ComponentType>>(map->at(index));
	}

	template<class ComponentType, class ChildrenType>
	void AddComponentChildren(std::shared_ptr<ComponentType> parent, std::shared_ptr<ChildrenType> child)
	{
		child->SetParent(parent);
		parent->AddChildren(child);
	}

	template<typename ComponentType>
	void DoForEach2DEntity(Function<ComponentType> func)
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

	template<typename ComponentType>
	void DoForEach3DEntity(Function<ComponentType> func)
	{
		for (auto& componentPtr : m_3DComponentsMap)
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

	ComponentsPtrMap& GetAllComponents(const ComponentDimension type)
	{
		if (type == ComponentDimension::TwoD)
		{
			return m_ComponentsMap;
		}

		return m_3DComponentsMap;
	}

private:
	ComponentsPtrMap m_ComponentsMap;
	ComponentsPtrMap m_3DComponentsMap;
	AvailableIDsVec m_AvailableIDs;
	AvailableIDsVec m_3DAvailableIDs;
};