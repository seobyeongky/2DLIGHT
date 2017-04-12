/*
Apply box2d body to all objects
*/

#include <stdio.h>


#include "applyBody.h"
#include "global.h"

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, 
	const int* tiles, unsigned int width, unsigned int height, 
	b2World* world, GameData* gameData)
{

	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset))
		return false;

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);


	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{

			// get the current tile number
			int tileNumber = tiles[i + j * width];
			
			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			// tilenumber % (130 / 32)  ==> tilenumber % 4.0625
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 corners
			int fixJ = height - j - 1;
			quad[0].position = sf::Vector2f(i * tileSize.x, fixJ * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, fixJ * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (fixJ + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (fixJ + 1) * tileSize.y);
			if (tileNumber < 2){
				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

			}
			
			if (tileNumber == 1 || tileNumber ==4 )
			{

				//Set ground body
				b2BodyDef tempBody;
				//set position
				tempBody.position.Set((quad[0].position.x + quad[1].position.x) / 4, (quad[0].position.y + quad[1].position.y) / 4 + 8);   //character body position

				b2Body* tempbody = world->CreateBody(&tempBody);

				b2PolygonShape tempbox;
				//set size of ground box
				tempbox.SetAsBox((quad[1].position.x - quad[0].position.x) / 4, (quad[2].position.y - quad[1].position.y) / 4);
				
				tempbody->CreateFixture(&tempbox, 0.0f);
				if (tileNumber == 1)
					tempbody->SetUserData(int(0));
				else if (tileNumber == 4)
					tempbody->SetUserData((int*)(4));
			}
			else if (tileNumber == 2)
			{
				sf::Sprite _sprite = imageLoad.getPlyrSprite();
				sf::Texture _texture = imageLoad.getCharTexture();
				Player plyr(_texture, _sprite,
					(quad[0].position.x + quad[1].position.x) / 4,
					(quad[0].position.y + quad[1].position.y) / 4 + 8,
					_sprite.getScale().x*_texture.getSize().x / 2,
					_sprite.getScale().y*_texture.getSize().y / 2,
					200.0f, 0.05f);
				plyr.setBody(b2_dynamicBody, true);
				_sprite = plyr.getSprite();
				_sprite.setPosition(plyr.getBody()->GetPosition().x,
					plyr.getBody()->GetPosition().y);

				gameData->setPlayer(plyr);
				//sf::Sprite _sprite = gameData->loadSprite(1);
				//sf::Texture _texture = bodyAppiler.getTexture();
				//Player plyr(_texture, _sprite,
				//	(quad[0].position.x + quad[1].position.x) / 4,
				//	(quad[0].position.y + quad[1].position.y) / 4 + 8,
				//	_sprite.getScale().x*_texture.getSize().x / 2,
				//	_sprite.getScale().y*_texture.getSize().y / 2,
				//	200.0f, 0.05f);
				////Texture, sprite, X position, Y position, width, height
				//
				//plyr.setBody(b2_dynamicBody, true);

				//_sprite = plyr.getSprite();
				//_sprite.setPosition(plyr.getBody()->GetPosition().x,
				//	plyr.getBody()->GetPosition().y);

				//gameData->setPlyr(plyr);




			}
			
			
			else if (tileNumber == 3)
			{
				float length = (quad[1].position.x - quad[0].position.x)/2;
				float currentX = (quad[0].position.x + quad[1].position.x)/4;
				float currentY = (quad[0].position.y + quad[1].position.y) / 4 + 8;

				float left_End = currentX - length;
				float right_End = currentX + length;
				zombie * z_1 = new zombie(1, currentX, currentY, left_End, right_End);
				
				z_1->setBody(b2_dynamicBody, true);
				gameData->setZombie(z_1);
				
				//gameData->setZombie(z_1);


			}
		}

	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_vertices, states);
}


void debugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

	}

void debugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
		int temp_VertexCount = vertexCount + 1;
		sf::Vertex * sfVertices = new sf::Vertex[temp_VertexCount];

		for (int i = 0; i < temp_VertexCount; ++i) {
			sfVertices[i] = sf::Vertex(sf::Vector2f(vertices[i].x, vertices[i].y));
			sfVertices[i].color = sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
		}
		sfVertices[temp_VertexCount - 1] = sfVertices[0];
		window.draw(sfVertices, temp_VertexCount, sf::LinesStrip);
	}

void debugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {

	}

void debugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {

	}

void debugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)  {

	}

void debugDraw::DrawTransform(const b2Transform& xf) {

	}

void debugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)  {

	}


applyBody::applyBody()
	/*: zombieCount(0), _zombies(new zombie*[3])*/
{}

TileMap applyBody::applyMapTile(const std::string& tileset, sf::Vector2u tileSize,
	const int* tile, unsigned int width, unsigned int height, b2World* world)
{
	TileMap buildmap;
	if (!buildmap.load("tileset.jpg", sf::Vector2u(32, 32), tile,
		20, 10, world, getGameData()))
		exit(1);
	return buildmap;
}

GameData* applyBody::getGameData() { return &save_data; }

//void applyBody::setPlyr(Player player) {
//	_player = player;
//}
//
//void applyBody::setZombie(zombie* zombiePtr)
//{
//	*(_zombies+zombieCount) = zombiePtr;
//	zombieCount++;
//}
//
//sf::Sprite applyBody::loadSprite(int obj)
//{
//	tmpTexture = load_Image.getCharTexture();
//	switch (obj) {
//	case 1:
//		tmpSprite = load_Image.getCharSprite();
//		break;
//	case 2:
//		tmpSprite = load_Image.getZombieSprite();
//		break;
//	case 3:
//		break;
//	case 4:
//		break;
//	}
//
//	return tmpSprite;
//}
//
//zombie* applyBody::getZombie(int index)
//{
//	return *(_zombies + (index));
//}
//
//sf::Texture applyBody::getTexture() { return tmpTexture; }
//
//Player applyBody::getPlayer() { return _player; }