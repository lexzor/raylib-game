#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw()
{
	ComponentsManager::get().DoForEachEntity<DrawableComponent>([](std::shared_ptr<DrawableComponent> component) {
		if (component->IsDrawable())
		{
			component->OnDraw();
		}
	});
}
