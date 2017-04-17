#include "renderer.h"
#include "window.h"

using namespace sf;

Renderer* renderer;

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::RegisterDrawable(Drawable * drawable)
{
	drawables.push_back(drawable);
}

void Renderer::RenderAll()
{
	for (Drawable* drawable : drawables)
	{
		window.draw(*drawable);
	}
}

void MakeRenderer()
{
	renderer = new Renderer();
}