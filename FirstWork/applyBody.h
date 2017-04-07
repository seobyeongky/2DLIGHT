#pragma once
/*
applyBody.h
*/
#include <SFML\Graphics.hpp>
#include "Box2D/Box2D.h"

#include "Player.h"
#include "zombie.h"



class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, b2World* world);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

};


class debugDraw : public b2Draw  // child class : parent class
								 //Draw boxes using box2D engine 
{
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)override;
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)override;
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	virtual void DrawTransform(const b2Transform& xf) override;
	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;
};

class applyBody {
public:
	TileMap applyMapTile(const std::string& tileset, sf::Vector2u tileSize, const int* tile, unsigned int width, unsigned int height, b2World* world);

	applyBody();
	sf::Sprite loadSprite(int object);
	sf::Texture getTexture();
	void setPlyr(Player player);
	Player getPlayer();
	void setZombie(zombie* _zombie);
	zombie *getZombie(int index);

	int zombieCount;
/*
	void setPlayer(b2Body* body);
	b2Body* getPlayer();
	b2Body* setBody(b2BodyType bodyType, bool fixRotation);
	void addSprite_Body();
	void setPosition(float x, float y);
	void setPhysics(float density, float friction);
	void setBoxSize(float width, float height);
	*/
	
private:
	/*float position_x;
	float position_y;
	float objDensity;
	float objFriction;
	
	float boxSize_width;
	float boxSize_height;

	b2Body* player;
	b2Body* body;
	*/
	Player _player;
	zombie** _zombies;
	sf::Sprite tmpSprite;
	sf::Texture tmpTexture;
};