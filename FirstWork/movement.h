#pragma once

#include <Box2D\Box2D.h>
#include "GameData.h"

#define MAX_SPEED 40
enum zombieStatus {
	Air,
	Ground
};
enum moveDir {
	LEFT =0,
	RIGHT,
	UP,
	SAMEFLOOR
};
class movement {
public:
	zombieStatus status;
	movement();
	movement(GameData* gamedata);
	void movePlayer(b2Body* body, moveDir dir);
	void moveZombie(b2Body* body, b2Vec2 speed);
	void jumpZombie(b2Body* body);

	void moveZombie_default(b2Body* body, moveDir dir);
	void moveZombie_setSpeed(b2Body* body, moveDir dir, b2Vec2 speed);
	void setIndex(int index);
private:
	GameData* gameData;
	int _index;
};