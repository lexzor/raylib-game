#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw2D()
{
	ComponentsManager::get().DoForEach2DEntity<DrawableComponent>([](std::shared_ptr<DrawableComponent> component) {
		if (component->IsDrawable())
		{
			component->OnDraw();
		}
	});
}

void Renderer::Draw3D()
{
	ComponentsManager::get().DoForEach3DEntity<DrawableComponent>([](std::shared_ptr<DrawableComponent> component) {
		if (component->IsDrawable())
		{
			component->OnDraw();
		}
	});
}