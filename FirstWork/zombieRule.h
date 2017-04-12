#pragma once
#include <Box2D\Box2D.h>
#include "movement.h"
#include "GameData.h"
class zombieRule {
public:
	zombieRule();
	zombieRule(GameData* game_data);
	bool checkPosition(b2Vec2 c_position);
	b2Vec2 getOriPosition();
	void movementLimits(b2Body* z_body, GameData* gameData);

	//void setIndex(int i);

	moveDir x_chase(b2Vec2 start_position, b2Vec2 dest_position);
	moveDir y_chase(b2Vec2 start_position, b2Vec2 dest_position);
private:
	int zombieIndex;
	GameData* _gameData;
};