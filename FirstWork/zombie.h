#pragma once

/*
zombie.h
*/
#include "AvatarProperty.h"
#include "loadImage.h"
class zombie {
public:
	zombie(int zombieType, float _x, float _y,
		float p_left, float p_right);
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
	loadImage imageLoad;
	sf::Sprite z_Sprite;
	sf::Texture z_Texture;
	sf::Text dbug;
	b2Vec2 ori_position;
};

