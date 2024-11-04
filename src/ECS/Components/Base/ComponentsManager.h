#pragma once

#include "Component.h"

#include <vector>
#include <memory>
#include <cstdint>
#include <functional>

class ComponentsManager
{
public:
	using ComponentsPtrMap = std::vector<std::shared_ptr<Component>>;
public:
	ComponentsManager() {};
	~ComponentsManager() {};

	static ComponentsManager& GetInstance()
	{
		static ComponentsManager instance;
		return instance;
	}

	template<class ComponentType, typename ...Args>
	std::shared_ptr<ComponentType> CreateComponent(Args&& ...args)
	{
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>(std::forward<Args>(args)...);
		m_ComponentsMap.push_back(static_cast<std::shared_ptr<Component>>(component));

		return component;
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> GetComponent(const uint64_t& index)
	{
		if (m_ComponentsMap[index].get() != nullptr)
		{
			return static_cast<std::shared_ptr<ComponentType>>(m_ComponentsMap[index]);
		}

		return nullptr;
	}

	template<typename ComponentType>
	void DoForEachEntity(std::function<void(std::shared_ptr<ComponentType>)> func)
	{
		for (auto& componentPtr : m_ComponentsMap)
		{
			func(std::dynamic_pointer_cast<ComponentType>(componentPtr));
		}
	}

private:
	ComponentsPtrMap m_ComponentsMap;
};