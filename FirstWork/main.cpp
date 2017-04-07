/*
Main cpp

*/


#define _CRT_SECURE_NO_WARNINGS 1
#define _USE_MATH_DEFINES


#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <stdio.h>
#include <math.h>

#include "Box2D/Box2D.h"
#include "zombieAI.h"
#include "applyBody.h"
#include "maps.h"
#include "loadImage.h"
sf::RenderWindow window(sf::VideoMode(1200, 600), "First game");
b2World* world;
applyBody bodyApplier;
loadImage load_Image;
sf::Font font;

enum Player_Status {
	dead,
	ground,
	air
};

static Player_Status status = ground;
typedef void(*collision_handler)();

collision_handler table[10][10] = { nullptr, };

class MyContactListener : public b2ContactListener {
	
	void BeginContact(b2Contact* contact)
	{
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	
		if (bodyUserData)
		{
		}
			
		void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData2)
		{
		}

		collision_handler handler = table[(int)bodyUserData][(int)bodyUserData2];

		if (handler != nullptr)
			handler();
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		b2Body* body1 = fixtureA->GetBody();
		b2Body* body2 = fixtureB->GetBody();
	}
	

	void EndContact(b2Contact* contact)
	{
	
	}	
};

void on_zombie_human_collide()
{
	
	status = dead;
}
void human_ground_collide()
{
	status = ground;
}

sf::VertexArray* vertices;
bool detact = false;
bool detactWall = false;


void drawReflectedRay(b2Vec2 p1, b2Vec2 p2)
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
			if (!f->RayCast(&output, input,0))
				continue;
			if (output.fraction < closestFraction) {
				closestFraction = output.fraction;
				intersectionNormal = output.normal;
			}

			if (b->GetUserData() == (int*)1)
				detact = true;
			else if (b->GetUserData() == (int*)4)
			{
				detactWall = true;
			}
		}
	}
	intersectionPoint = p1 + closestFraction * (p2 - p1);

/*
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(intersectionPoint.x, intersectionPoint.y);
	glEnd();*/

/*
	vertices[0] = sf::Vertex(sf::Vector2f(p1.x, p1.y));
	vertices[1] = sf::Vertex(sf::Vector2f(intersectionPoint.x, intersectionPoint.y));*/

	vertices->append(sf::Vertex(sf::Vector2f(p1.x, p1.y)));
	vertices->append(sf::Vertex(sf::Vector2f(intersectionPoint.x, intersectionPoint.y)));
	if (closestFraction == 1)
		return; //ray hit nothing so we can finish here
	if (closestFraction == 0)
		return;
	//still some ray left to reflect

	b2Vec2 remainingRay = (p2 - intersectionPoint);
	b2Vec2 projectedOntoNormal = b2Dot(remainingRay, intersectionNormal) * intersectionNormal;
	b2Vec2 nextp2 = p2 - 2 * projectedOntoNormal;

	//recurse

}


int main()
{
	table[1][2] = table[2][1] = on_zombie_human_collide;
	table[1][0] = table[0][1] = human_ground_collide;
	font.loadFromFile("arial.ttf");
	sf::Event event;
	debugDraw draw;
	movement move;
	zombieAI zombie_AI;
	b2Vec2 gravity(0.0f, -80.f);
	world = new b2World(gravity);
	MyContactListener contactListener;
	world->SetContactListener(&contactListener);
	
	maps tilemap;
	int *tile = tilemap.getmap();
	TileMap buildmap= bodyApplier.applyMapTile("tileset.jpg", sf::Vector2u(32, 32), tile, 20, 10, world);
	buildmap.setScale(0.5f,0.5f);
	window.setFramerateLimit(60U);


	auto mapHeight = buildmap.getScale().y * 10*32;

	sf::View view2;
	view2.setSize(sf::Vector2f(buildmap.getScale().x * 20 * 32, -mapHeight));
	view2.setCenter(sf::Vector2f(view2.getSize().x / 2, -(view2.getSize().y / 2))); //set center pixel

	Player _player = bodyApplier.getPlayer();
//	zombie* _zombie1 = bodyApplier.getZombie(1);

	b2Body* body = _player.getBody();
//	b2Body* z_body = _zombie1->getBody();
	//sf::Sprite _sprite = load_Image.getCharSprite(); 
	
	sf::Sprite _sprite = _player.getSprite();

	float32 timestep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	uint32 flags = b2Draw::e_shapeBit | b2Draw::e_aabbBit | b2Draw::e_centerOfMassBit | b2Draw::e_jointBit
		| b2Draw::e_pairBit;

	draw.SetFlags(flags);
	world->SetDebugDraw(&draw);


	


	while (window.isOpen())  //open window	
	{
		float rayLength = 50;

		vertices = zombie_AI.getVertices();
		vertices->clear();

		for (float i = -30; i < 30; i++)
		{
			for (int j = 0; j < bodyApplier.zombieCount; j++)
			{

				b2Body* z_body = bodyApplier.getZombie(j)->getBody();
				float currentRayAngle = i / 180 * M_PI;
				float currentSpeed = z_body->GetLinearVelocity().x;
				if (currentSpeed < 0)
					currentRayAngle = (i + 180) / 180 * M_PI;
				b2Vec2 p1(z_body->GetPosition().x, z_body->GetPosition().y); //center of scene
				b2Vec2 p2 = p1 + rayLength * b2Vec2(cosf(currentRayAngle), sinf(currentRayAngle));
			}
		}

		_sprite.setPosition(_player.getBody()->GetPosition().x,
			_player.getBody()->GetPosition().y);

		for (int i = 0; i < bodyApplier.zombieCount; i++)
		{
			b2Body* z_body = bodyApplier.getZombie(i)->getBody();
			zombie_AI.setIndex(i);
			zombie_AI.zombie_AI(body);
		/*}
		
		_sprite.setPosition(_player.getBody()->GetPosition().x,
			_player.getBody()->GetPosition().y);


		for (int i = 0; i < bodyApplier.zombieCount; i++)
		{*/
			sf::Sprite* z_sprite = bodyApplier.getZombie(i)->getSprite();
			z_sprite->setPosition(bodyApplier.getZombie(i)->getBody()->GetPosition().x,
				bodyApplier.getZombie(i)->getBody()->GetPosition().y);
			sf::Text* dbug = bodyApplier.getZombie(i)->getText();
			dbug->setPosition(z_sprite->getPosition());
		}
		
		if (status == dead)
		{
			body->SetTransform(b2Vec2(100.f, 50.f), 0);
			status = air;
		}
		world->Step(timestep, velocityIterations, positionIterations);
		while (window.pollEvent(event))
		{
			int* statustest = zombie_AI.get_value();
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				break;
			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			break;
						
			
			default:
					break;
			} 
		}


		window.clear(sf::Color::White);

		//study below codes
		for (int i = 0; i < bodyApplier.zombieCount; i++)
		{
			b2Body* z_body = bodyApplier.getZombie(i)->getBody();
			zombie* _zombie1 = bodyApplier.getZombie(i);
			zombie_AI.setIndex(i);
			if (!zombie_AI.status.detact_player)
			{
					
				if (z_body->GetPosition().x > _zombie1->leftEnd	&&
					z_body->GetPosition().x < _zombie1->rightEnd)
					zombie_AI.defaultPatrol(z_body, _zombie1,b2Vec2(0,0));

				else if (z_body->GetPosition().x <= _zombie1->leftEnd)
					zombie_AI.defaultPatrol(z_body, _zombie1, b2Vec2(50, z_body->GetLinearVelocity().y));
			
				else if (z_body->GetPosition().x >= _zombie1->rightEnd)
					zombie_AI.defaultPatrol(z_body, _zombie1, b2Vec2(-50, z_body->GetLinearVelocity().y));

			}
			else
			{
				zombie_AI.zombieStatus(z_body, body);
			}
		}
		////////////////////////////////////
		///Check the input of the keyboard
		///
		////////////////////////////////////
		for (int i = 0; i < 151; i++)
		{
			if (event.key.code == -1)
				break;
			else if (event.key.code == i)
			{
				break;
			}

//			int keyCodePressed = event.key.code;
	//		if (keyCodePressed == -1)
		//		break;
		}
/*
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			move.movePlayer(body, LEFT);
			break;
		case sf::Keyboard::Right:
			move.movePlayer(body, RIGHT);
			break;
		case sf::Keyboard::Space:
			if (status == ground)
			{
				move.movePlayer(body, UP);
				status = air;
			}
			break;
		default:
			break;
		}*/


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			move.movePlayer(body, LEFT);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			move.movePlayer(body, RIGHT);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			switch (status)
			{
			case air:
				break;
			case ground:
				move.movePlayer(body, UP);
				status = air;
				break;
			}
		}
		


		window.setView(view2);
		window.draw(buildmap);
		world->DrawDebugData(); // Draw data in b2draw
		window.draw(_sprite);
	
		vertices->setPrimitiveType(sf::Lines);
		window.draw(*vertices);
		for (int i = 0; i < bodyApplier.zombieCount; i++)
		{
			window.draw(*bodyApplier.getZombie(i)->getSprite());
			window.draw(*bodyApplier.getZombie(i)->getText());
		}

		window.display();
	}
}