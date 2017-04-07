#pragma once
/*
zombie.cpp
*/
#include "zombie.h"
#include "global.h"


zombie::zombie(int zombieType, float _x, float _y, float left, float right) :
	zombieType(zombieType),
	leftEnd(left),rightEnd(right),currentX(_x),currentY(_y){
	/*
	Load texture and sprite in constructor
	Use them to set box size and physics
	based on zombieType, different texture and sprites will be called
	*/
	dbug.setFont(font);
	dbug.setString("zombie");
	dbug.setScale(sf::Vector2f(0.5f, -1));
	ori_position.x = _x;
	ori_position.y = _y;
	
	z_Sprite = bodyApplier.loadSprite(zombieType+1);
	z_Texture = bodyApplier.getTexture();
	switch (zombieType)
	{
	case 1:
		zombieProperty.setPosition(_x, _y);
		zombieProperty.setBoxSize(z_Sprite.getScale().x*z_Texture.getSize().x / 2,
			z_Sprite.getScale().y*z_Texture.getSize().y / 2);
		zombieProperty.setPhysics(200.0f, 1.0f);
		break;
	case 2:
		break;
	default:
		break;
	}

}

void zombie::setBody(b2BodyType bodyType, bool fixRotation)
{
	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;

	bodyDef.type = bodyType;
	bodyDef.position.Set(zombieProperty.getPosition().x,
		zombieProperty.getPosition().y);
	z_body = world->CreateBody(&bodyDef);
	dynamicBox.SetAsBox(zombieProperty.getBoxSize('w'),
		zombieProperty.getBoxSize('h'));
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = zombieProperty.getPhysics('d');
	fixtureDef.friction = zombieProperty.getPhysics('f');

	z_body->CreateFixture(&fixtureDef);
	z_body->SetUserData((int*)2);
	if (fixRotation)
		z_body->SetFixedRotation(0x0010);
}
sf::Text *zombie::getText() { return &dbug; }
sf::Sprite *zombie::getSprite() { return &z_Sprite; }
sf::Texture zombie::getTexture() { return z_Texture; }
b2Body* zombie::getBody() { return z_body; }
b2Vec2 zombie::getOriPosition() { return ori_position; }