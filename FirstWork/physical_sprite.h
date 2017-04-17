#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

#include "body_meta.h"


class PhysicalSprite : public sf::Drawable, public sf::Transformable
{
public:
	PhysicalSprite(const sf::Vector2f & pos
		, const sf::Sprite & spriteToUse
		, BodyType bodyType
		, float boxWidth, float boxHeight);
	virtual ~PhysicalSprite();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite sprite;
};

