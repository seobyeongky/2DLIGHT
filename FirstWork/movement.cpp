#include "movement.h"
#include "global.h"
#include <SFML\Graphics.hpp>

void movement::movePlayer(b2Body* body, moveDir dir)
{
	if (dir == LEFT)
	{
		if (body->GetLinearVelocity().x == 0)
			body->SetLinearVelocity(b2Vec2(-10, body->GetLinearVelocity().y));
		if (body->GetLinearVelocity().x < -30)
			body->SetLinearVelocity(b2Vec2(-30, body->GetLinearVelocity().y));
		else
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x - 1, body->GetLinearVelocity().y));

	}
	else if (dir == RIGHT)
	{
		if (body->GetLinearVelocity().x == 0)
			body->SetLinearVelocity(b2Vec2(10, body->GetLinearVelocity().y));
		else if (body->GetLinearVelocity().x > 30)
			body->SetLinearVelocity(b2Vec2(30, body->GetLinearVelocity().y));
		else
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x + 1, body->GetLinearVelocity().y));
	}
	else if(dir == UP)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 60));
	}

}

//void movement::movePlayer(b2Body* body, moveDir dir)
//{
//	switch (dir)
//	{
//	case LEFT:
//		if (body->GetLinearVelocity().x == 0)
//			body->SetLinearVelocity(b2Vec2(-10, body->GetLinearVelocity().y));
//		if (body->GetLinearVelocity().x < -30)
//			body->SetLinearVelocity(b2Vec2(-30, body->GetLinearVelocity().y));
//		else
//			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x - 1, body->GetLinearVelocity().y));
//		break;
//
//	case RIGHT:
//
//		if (body->GetLinearVelocity().x == 0)
//			body->SetLinearVelocity(b2Vec2(10, body->GetLinearVelocity().y));
//		else if (body->GetLinearVelocity().x > 30)
//			body->SetLinearVelocity(b2Vec2(30, body->GetLinearVelocity().y));
//		else
//			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x + 1, body->GetLinearVelocity().y));
//		break;
//	case UP:
//		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 60));
//		break;
//	case DOWN:
//
//		break;
//
//	}
//
//};


void movement::moveZombie(b2Body*body, b2Vec2 speed)
{
	body->SetLinearVelocity(speed);
}
void movement::jumpZombie(b2Body * body)
{
	moveZombie(body, b2Vec2(body->GetLinearVelocity().x, 60));
}
void movement::moveZombie_default(b2Body* body, moveDir dir)
{

	sf::Text* txt = bodyApplier.getZombie(_index)->getText();
	switch (dir)
	{
	case LEFT:
		moveZombie(body,(b2Vec2(-30, body->GetLinearVelocity().y)));
		txt->setString("MOVE_LEFT");
		break;
	case RIGHT:
		moveZombie(body, (b2Vec2(30, body->GetLinearVelocity().y)));
		txt->setString("MOVE_RIGHT");
		break; 
	case UP:
		jumpZombie(body);
		txt->setString("JUMP");
		break;
	}
}

void movement::moveZombie_setSpeed(b2Body * body, moveDir dir, b2Vec2 speed)
{
	sf::Text* txt = bodyApplier.getZombie(_index)->getText();
	switch (dir)
	{
	case LEFT:
		speed.x = -(speed.x);
		moveZombie(body,speed);
		txt->setString("MOVE_LEFT_BOOST");
		break;
	case RIGHT:
		moveZombie(body, speed);
		txt->setString("MOVE_RIGHT_BOOST");
		break;
	}
}

void movement::setIndex(int index)
{
	_index = index;
}
