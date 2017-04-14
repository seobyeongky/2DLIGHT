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
#include "GameData.h"

sf::RenderWindow window(sf::VideoMode(1200, 600), "First game");
b2World* world;
applyBody bodyApplier;
sf::Font font;

enum Avatar_Status {
	dead,
	ground,
	air
};

static Avatar_Status player_status = ground;
static Avatar_Status zombie_Status = ground;
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
	player_status = dead;
}
void human_ground_collide()
{
	player_status = ground;
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
	

	GameData* gameData = new GameData();
	font.loadFromFile("arial.ttf");
	
	b2Vec2 gravity(0.0f, -80.f);
	world = new b2World(gravity);
	
	maps tilemap;
	int *tile = tilemap.getmap();
	TileMap buildmap= bodyApplier.applyMapTile(
		"tileset.jpg", sf::Vector2u(32, 32), tile, 20, 10,
		world, gameData);
	buildmap.setScale(0.5f,0.5f);
	window.setFramerateLimit(60U);

	//////////////////////////////////////
	sf::Event event;
	debugDraw draw;
	movement move(gameData);
	zombieAI zombie_AI(gameData, move);
	MyContactListener contactListener;
	world->SetContactListener(&contactListener);
	auto mapHeight = buildmap.getScale().y * 10*32;
	/////////////////////////////////////
	sf::View view2;
	view2.setSize(sf::Vector2f(buildmap.getScale().x * 20 * 32, -mapHeight));
	view2.setCenter(sf::Vector2f(view2.getSize().x / 2, -(view2.getSize().y / 2))); //set center pixel

	Player* _player = gameData->getPlayer();
	b2Body* body = _player->getBody();
	
	sf::Sprite* _sprite = _player->getSprite();

	float32 timestep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	uint32 flags = b2Draw::e_shapeBit | b2Draw::e_aabbBit | b2Draw::e_centerOfMassBit | b2Draw::e_jointBit
		| b2Draw::e_pairBit;

	draw.SetFlags(flags);
	world->SetDebugDraw(&draw);


	///////////////////////////////////////
	loadImage image_load;
	sf::Sprite testSprite = image_load.getPlyrSprite();
	///////////////////////////////////////


	while (window.isOpen())  //open window	
	{
		float rayLength = 50;

		vertices = zombie_AI.getVertices();
		vertices->clear();

		_sprite->setPosition(_player->getBody()->GetPosition().x,
			_player->getBody()->GetPosition().y);
		/////////////////////////////

		testSprite.setPosition(_sprite->getPosition().x-15, _sprite->getPosition().y);
		/////////////////////////////////

		for (int i = 0; i < gameData->zombie_count; i++)
		{
			b2Body* z_body = gameData->getZombie(i)->getBody();
			gameData->setIndex(i);
			zombie_AI.zombie_AI(body);

			sf::Sprite* z_sprite = gameData->getZombie(i)->getSprite();
			z_sprite->setPosition(
				gameData->getZombie(i)->getBody()->GetPosition().x,
				gameData->getZombie(i)->getBody()->GetPosition().y);

			sf::Text* dbug = gameData->getZombie(i)->getText();
			dbug->setPosition(z_sprite->getPosition());
		}
		
		if (player_status == dead)
		{
			body->SetTransform(b2Vec2(100.f, 50.f), 0);
			player_status = air;
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

		for (int i = 0; i < gameData->zombie_count; i++)
		{
			b2Body* z_body = gameData->getZombie(i)->getBody();
			zombie* _zombie1 = gameData->getZombie(i);
			gameData->setIndex(i);
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
				zombie_AI.chase(z_body, body);
			}
		}
		////////////////////////////////////
		///Check the input of the keyboard
		///
		////////////////////////////////////
		/*for (int i = 0; i < 151; i++)
		{
			if (event.key.code == -1)
				break;
			else if (event.key.code == i)
			{
				break;
			}
*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			move.movePlayer(body, LEFT);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			move.movePlayer(body, RIGHT);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			switch (player_status)
			{
			case air:
				break;
			case ground:
				move.movePlayer(body, UP);
				player_status = air;
				break;
			}
		}
		


		window.setView(view2);
		window.draw(buildmap);
		world->DrawDebugData(); // Draw data in b2draw
	
		vertices->setPrimitiveType(sf::Lines);
		window.draw(*vertices);
		for (int i = 0; i < gameData->zombie_count; i++)
		{
			window.draw(*gameData->getZombie(i)->getSprite());
			window.draw(*gameData->getZombie(i)->getText());
		}
		window.draw(*_sprite);
		//window.draw(testSprite);
		window.display();
	}
}