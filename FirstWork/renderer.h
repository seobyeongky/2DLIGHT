#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void RegisterDrawable(sf::Drawable* drawable);
	void RenderAll();

private:
	std::vector<sf::Drawable*> drawables;
};

extern Renderer* renderer;

void MakeRenderer();