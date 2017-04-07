#pragma once

/*
AvatarProperty.h
*/
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

class AvatarProperty {

public:

	//Consider changing below codes as constructor
	void setPosition(float x, float y);
	void setPhysics(float density, float friction);
	void setBoxSize(float width, float height);

	b2Vec2 getPosition();
	float getPhysics(char physic);
	float getBoxSize(char geometry);

private:
	b2Vec2 position;
	float objDensity;
	float objFriction;

	float boxSize_width;
	float boxSize_height;

};