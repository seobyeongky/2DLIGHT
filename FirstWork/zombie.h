#pragma once

/*
zombie.h
*/
#include "AvatarProperty.h"

class zombie {
public:
	zombie(int zombieType, float _x, float _y,
		float moveLeft, float moveRight);
	zombie();
	void setBody(b2BodyType bodyType, bool fixRotation);
	sf::Sprite *getSprite();
	sf::Texture getTexture();
	b2Body* getBody();
	sf::Text *getText();
	b2Vec2 getOriPosition();
	float leftEnd, rightEnd, currentX, currentY;
private:
	int zombieType;
	b2Body* z_body;
	AvatarProperty zombieProperty;
	sf::Sprite z_Sprite;
	sf::Texture z_Texture;
	sf::Text dbug;
	b2Vec2 ori_position;
};

