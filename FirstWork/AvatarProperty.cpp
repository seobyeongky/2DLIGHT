#include "AvatarProperty.h"

/*
AvatarProperty.cpp
*/
void AvatarProperty::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

void AvatarProperty::setPhysics(float density, float friction) {

	objDensity = density;
	objFriction = friction;
}

void AvatarProperty::setBoxSize(float width, float height) {

	boxSize_width = width;
	boxSize_height = height;
}


b2Vec2 AvatarProperty::getPosition()
{
	return position;
}

float AvatarProperty::getPhysics(char physics)
{
	if (physics == 'd')
		return objDensity;
	else if (physics == 'f')
		return objFriction;
}


float AvatarProperty::getBoxSize(char geometry)
{
	if (geometry == 'w')
		return boxSize_width;
	else if (geometry == 'h')
		return boxSize_height;
}