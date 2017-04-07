#include "Player.h"
#include "global.h"

Player::Player(sf::Texture _texture, sf::Sprite _sprite
	, float _x, float _y
	, float _width, float _height
	, float _density, float _friction) :

	plyTexture(_texture), plySprite(_sprite) {
	
	plyProperty.setPosition(_x, _y);
	plyProperty.setBoxSize(_width, _height);
	plyProperty.setPhysics(_density, _friction);

}
Player::Player()
{

}

sf::Texture Player::getTexture() {
	return plyTexture;
}

sf::Sprite Player::getSprite() {
	return plySprite;
}

void Player::setBody(b2BodyType bodyType, bool fixRotation) {
	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;

	bodyDef.type = bodyType;
	bodyDef.position.Set(plyProperty.getPosition().x, 
		plyProperty.getPosition().y);

	plyBody = world->CreateBody(&bodyDef);

	dynamicBox.SetAsBox(plyProperty.getBoxSize('w'),
		plyProperty.getBoxSize('h'));
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = plyProperty.getPhysics('d');
	fixtureDef.friction = plyProperty.getPhysics('f');

	plyBody->CreateFixture(&fixtureDef);

	plyBody->SetUserData((int*)1);
	if (fixRotation)
		plyBody->SetFixedRotation(0x0010);
}

b2Body* Player::getBody() {
	return plyBody;

}