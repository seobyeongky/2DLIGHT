/*
zombieAI.cppp
*/

#define _USE_MATH_DEFINES

#include "zombieAI.h"
#include "global.h"
#include <math.h>

int zombieAI::zombie_index=0;
void zombieAI::setIndex(int index)
{
	zombie_index = index;
	move.setIndex(index);
	rule.setIndex(index);
}


void zombieAI::defaultPatrol(b2Body* z_body, zombie* _zombie,b2Vec2 set_speed)
{

	b2Vec2 position = z_body->GetPosition();
	b2Vec2 speed = z_body->GetLinearVelocity();
	rule.movementLimits(z_body); //check and limit zombie speed 
	if (rule.checkPosition(position))
	{
		if (set_speed == b2Vec2(0, 0))
		{
			/*if (position.x == _zombie->currentX)
				move.moveZombie_default(z_body, LEFT);
			else */if (speed.x <= 0 && speed.x>-30)
				move.moveZombie_default(z_body, LEFT);
			else if (speed.x > 0 && speed.x < 30)
				move.moveZombie_default(z_body, RIGHT);
		}
		else
		{
			if (position.x == _zombie->currentX)
				move.moveZombie_setSpeed(z_body, LEFT, set_speed);
			else if (speed.x <= 0 && speed.x>-30)
				move.moveZombie_setSpeed(z_body, LEFT, set_speed);
			else if (speed.x > 0 && speed.x < 30)
				move.moveZombie_setSpeed(z_body, RIGHT, set_speed);
		}
	}
	else
	{
		runToGoal(z_body, rule.getOriPosition());
	}
}


void zombieAI::rayCasting(b2Vec2 p1, b2Vec2 p2)
{
	//set up input
	b2RayCastInput input;
	input.p1 = p1;
	input.p2 = p2;
	input.maxFraction = 1;

	//check every fixture of every body to find closest
	float closestFraction = 1; //start with end of line as p2
	b2Vec2 intersectionNormal(0, 0);
	b2Vec2 intersectionPoint(0, 0);
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput output;
			if (!f->RayCast(&output, input, 0))
				continue;
			if (output.fraction < closestFraction) {
				closestFraction = output.fraction;
				intersectionNormal = output.normal;
			}
			
			_value = (int*)(b->GetUserData());
			
		}
	}
	intersectionPoint = p1 + closestFraction * (p2 - p1);

	vertices.append(sf::Vertex(sf::Vector2f(p1.x, p1.y)));
	vertices.append(sf::Vertex(sf::Vector2f(intersectionPoint.x, intersectionPoint.y)));
	if (closestFraction == 1)
		return; //ray hit nothing so we can finish here
	if (closestFraction == 0)
		return;	//still some ray left to reflect
}

int* zombieAI::get_value() {
	return _value;
}
sf::VertexArray* zombieAI::getVertices()
{
	return &vertices;
}

void zombieAI::zombie_AI(b2Body* p_body)
{
	b2Body* z_body = bodyApplier.getZombie(zombie_index)->getBody();
	b2Vec2 z_position = z_body->GetPosition();
	b2Vec2 goal_position = p_body->GetPosition();

	for (float i = -30; i < 30; i++)
	{
		float currentRayAngle = i / 180 * M_PI;
		float currentSpeed = z_body->GetLinearVelocity().x;

		if (currentSpeed < 0)
			currentRayAngle = (i + 180) / 180 * M_PI;

		b2Vec2 p1(z_body->GetPosition().x, z_body->GetPosition().y); //center of scene
		b2Vec2 p2 = p1 + rayLength * b2Vec2(cosf(currentRayAngle), sinf(currentRayAngle));

		rayCasting(p1, p2);

		switch ((int)_value)
		{
		case 1:
			status.detact_player = true;
			continue;/*
		case 4:
			status.detact_wall = true;
			continue;*/
		default:
			status.detact_player = false;
			status.detact_wall = false;
			break;
		}
	}

}
void zombieAI::runToGoal(b2Body * zombie, b2Vec2 dest_position)
{
	b2Vec2 zombie_position = zombie->GetPosition();
	do
	{
		if (dest_position.x - zombie_position.x > 0)
			move.moveZombie_default(zombie, RIGHT);
		else if (dest_position.x - zombie_position.x < 0)
			move.moveZombie_default(zombie, LEFT);
		else if (dest_position.x - zombie_position.x == 0)
			break;
	}while (zombie_position == dest_position);
}

void zombieAI::zombieStatus(b2Body* z_body, b2Body* p_body)
{
	if (status.detact_player)
		chase( z_body, p_body);
}
void zombieAI::chase(b2Body * z_body, b2Body * p_body)
{
	b2Vec2 zombie_position = z_body->GetPosition();
	b2Vec2 dest_position = p_body->GetPosition();
	moveDir tmp_x_dir, tmp_y_dir;
	do
	{
		tmp_x_dir =rule.x_chase(zombie_position, dest_position);
		tmp_y_dir = rule.y_chase(zombie_position, dest_position);
		move.moveZombie_default(z_body, tmp_x_dir);
		if (status.detact_wall)
			move.moveZombie_default(z_body, tmp_y_dir);
	} while (zombie_position == dest_position);
}