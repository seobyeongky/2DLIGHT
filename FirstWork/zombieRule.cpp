#include "zombieRule.h"
#include "global.h"
zombieRule::zombieRule(){}

zombieRule::zombieRule(GameData* game_data)
	:_gameData(game_data) {

}


bool zombieRule::checkPosition(b2Vec2 c_position)
{
	zombieIndex = _gameData->getIndex();
	b2Vec2 ori_position = _gameData->getZombie(zombieIndex)->getOriPosition();
	const float epsilon = 0.01;
	if (c_position.x<_gameData->getZombie(zombieIndex)->rightEnd
		&&
		c_position.x>_gameData->getZombie(zombieIndex)->leftEnd)
	{
		return true;
	}
	else if (fabs(c_position.x - ori_position.x)<epsilon)
	{
		return true;
	}

	return false;
}

b2Vec2 zombieRule::getOriPosition()
{
	zombieIndex = _gameData->getIndex();
	return _gameData->getZombie(zombieIndex)->getOriPosition();
}

void zombieRule::movementLimits(b2Body* z_body, GameData* gameData)
{
	if (_gameData == nullptr)
		_gameData = gameData;
	float x_speed = z_body->GetLinearVelocity().x;
	float y_Speed = z_body->GetLinearVelocity().y;
	if (x_speed < -(MAX_SPEED))
		z_body->SetLinearVelocity(b2Vec2(-(MAX_SPEED), y_Speed));
	else if (x_speed > MAX_SPEED)
		z_body->SetLinearVelocity(b2Vec2(MAX_SPEED, y_Speed));
}
//
//void zombieRule::setIndex(int i) { 
//	zombieIndex = i; 
//}

moveDir zombieRule::x_chase(b2Vec2 start_position, b2Vec2 dest_position)
{
	if (dest_position.x - start_position.x > 0)
		return RIGHT;
	else if (dest_position.x - start_position.x < 0)
		return LEFT;
}

moveDir zombieRule::y_chase(b2Vec2 start_position, b2Vec2 dest_position)
{
	if (dest_position.x - start_position.x < 32.f)
		return SAMEFLOOR;
	else
		return UP;
}