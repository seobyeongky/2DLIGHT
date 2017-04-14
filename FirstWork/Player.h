#pragma once
/*
player.h
*/
#include "AvatarProperty.h"
#include "loadImage.h"


class Player {

public:
	Player(float _x, float _y, float _density, float _friction);
	Player();
	sf::Sprite *getSprite();
	sf::Texture getTexture();
	void setBody(b2BodyType bodyType, bool fixRotation);
	b2Body* getBody();
private:
	b2Body* plyBody;
	AvatarProperty plyProperty;
	loadImage imageLoad;
	sf::Sprite plySprite;
	sf::Texture plyTexture;
};