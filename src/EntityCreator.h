#pragma once

#include "ResourceManager.h"
#include "DeveloperConsole.h"
#include "ECS/Components/Rectangle.h"
#include "ECS/Components/Text.h"
#include "ECS/Components/Model.h"
#include "ECS/Components/Base/ComponentsManager.h"

class EntityCreator
{
public:
	EntityCreator();
	~EntityCreator();

	void Init();
	void OnFrame();
	bool CanCreateEntity() const;
	bool CanSetModel() const;

private:
	void PrintModels();
	void SaveEntity();
	void CreateEntity(const std::string& name);
	void SetModel(const std::string& name);

private:
	bool m_Enabled = false;

	std::shared_ptr<ecs::Rectangle> m_ContentBox = nullptr;
	std::shared_ptr<ecs::Text> m_Title = nullptr;
	std::shared_ptr<ecs::Text> m_CurrentModelName = nullptr;
	std::shared_ptr<ecs::Text> m_CurrentWorldModel = nullptr;
	std::shared_ptr<ecs::Model> m_Model = nullptr;
};