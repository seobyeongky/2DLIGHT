#pragma once
/*
player.h
*/
#include "AvatarProperty.h"


class Player {

public:
	Player(sf::Texture _texture, sf::Sprite _sprite
		, float _x, float _y
		, float _width, float _height
		, float _density, float _friction);
	Player();
	sf::Sprite getSprite();
	sf::Texture getTexture();
	void setBody(b2BodyType bodyType, bool fixRotation);
	b2Body* getBody();
private:
	b2Body* plyBody;
	AvatarProperty plyProperty;
	sf::Sprite plySprite;
	sf::Texture plyTexture;
};