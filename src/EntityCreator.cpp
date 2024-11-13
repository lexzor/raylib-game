#include "EntityCreator.h"

EntityCreator::EntityCreator()
{
}

EntityCreator::~EntityCreator()
{
}

void EntityCreator::Init()
{
	DevCon().RegisterConCommand("print_models", [this](const std::string& input) { this->PrintModels(); });
	DevCon().RegisterConCommand("create_entity", [this](const std::string& input) {
		if (!this->CanCreateEntity())
		{
			return;
		}

		std::string fullInput = input.data();
		std::string name = fullInput.erase(0, strlen("create_entity "));

		if (name.empty())
		{
			conprint_r("Invalid entity name");
			return;
		}

		this->CreateEntity(name);
	});
	DevCon().RegisterConCommand("set_model", [this](const std::string& input) {
		if (!this->CanSetModel())
		{
			conprint_r("You need to create an entity first");
			return;
		}

		std::string fullInput = input.data();
		std::string name = fullInput.erase(0, strlen("set_model "));

		if (name.empty())
		{
			conprint_r("Invalid model name");
			return;
		}

		this->SetModel(name);
	});

	m_ContentBox = ComponentsManager::get().Create2DComponent<ecs::Rectangle>(0, 100, 200, 400, Color{ 255,0,0, 100 });
	m_ContentBox->SetDrawable(false);
	m_ContentBox->SetExplicitLogic(true);

	m_Title = ComponentsManager::get().Create2DComponent<ecs::Text>(10, 10, "Entity Creator Info", 14, Color{ 255,255,255,255 });

	m_CurrentModelName = ComponentsManager::get().Create2DComponent<ecs::Text>(10, 30, "Name: ", 14, Color{ 255,255,255,255 });

	m_CurrentWorldModel = ComponentsManager::get().Create2DComponent<ecs::Text>(10, 50, "Model path: ", 14, Color{ 255,255,255,255 });

	ComponentsManager::get().AddComponentChildren(m_ContentBox, m_Title);
	ComponentsManager::get().AddComponentChildren(m_ContentBox, m_CurrentModelName);
	ComponentsManager::get().AddComponentChildren(m_ContentBox, m_CurrentWorldModel);
}

void EntityCreator::SetModel(const std::string& name)
{
	std::shared_ptr<::Model> newModel = ResourceManager::get().GetModelByName(name);

	if (!newModel)
	{
		conprint_r("Invalid model '" + name + "'");
		return;
	}

	m_Model->model = newModel;
}

void EntityCreator::OnFrame()
{
	if (!IsCursorHidden())
	{
		return;
	}

	if (IsKeyPressed(KEY_E))
	{
		m_Enabled = !m_Enabled;

		m_Title->SetDrawable(m_Enabled);
		m_CurrentModelName->SetDrawable(m_Enabled);
		m_CurrentWorldModel->SetDrawable(m_Enabled);
	}
}

void EntityCreator::PrintModels()
{
	ResourceManager::ResourcesList models = ResourceManager::get().GetAvailableModels();
	conprint_g("There are a total of " + std::to_string(models.size()) + " available models");
	conprint("[Index] ModelName");
	conprint("");

	for (const auto& model : models)
	{
		conprint(model);
	}
}

void EntityCreator::SaveEntity()
{
}

void EntityCreator::CreateEntity(const std::string& name)
{
	m_Model = ComponentsManager::get().Create3DComponent<ecs::Model>();
	m_Model->SetName(name);
	conprint_g("Entity " + m_Model->GetName() + " created succesfully");
}

bool EntityCreator::CanCreateEntity() const
{
	if (!m_Enabled)
	{
		return false;
	}

	return true;
}

bool EntityCreator::CanSetModel() const
{
	if(!m_Enabled)
	{
		return false;
	}

	if (m_Model == nullptr)
	{
		return false;
	}

	return true;
}
