#include "World.h"
#include "window.h"
#include "config.h"

#include <SFML\Graphics.hpp>

class MyContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

private:
	template <typename T>
	void HandleContactEventFor(b2Contact* contact, T table);
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


b2World* world;
debugDraw* dbgDraw;
MyContactListener* contactListener;

collision_handler beginListenerTable[10][10] = { nullptr, };
collision_handler endListenerTable[10][10] = { nullptr, };

void CreateWorld()
{
	b2Vec2 gravity(0.0f, -80.f);
	world = new b2World(gravity);
	contactListener = new MyContactListener();
	world->SetContactListener(contactListener);

#ifdef DEBUG_DRAW
	dbgDraw = new debugDraw();
	uint32 flags = b2Draw::e_shapeBit | b2Draw::e_aabbBit | b2Draw::e_centerOfMassBit | b2Draw::e_jointBit
		| b2Draw::e_pairBit;

	dbgDraw->SetFlags(flags);
	world->SetDebugDraw(dbgDraw);
#endif
}

void OnBeginContact(BodyType typeLhs, BodyType typeRhs, collision_handler handler)
{
	beginListenerTable[typeLhs][typeRhs] = handler;
}

void OnEndContact(BodyType typeLhs, BodyType typeRhs, collision_handler handler)
{
	endListenerTable[typeLhs][typeRhs] = handler;
}


// MyContactListener
template <typename T>
void MyContactListener::HandleContactEventFor(b2Contact* contact, T table)
{
	b2Body* bodyLhs = contact->GetFixtureA()->GetBody();
	b2Body* bodyRhs = contact->GetFixtureB()->GetBody();
	BodyMeta* metaLhs = static_cast<BodyMeta*>(bodyLhs->GetUserData());
	BodyMeta* metaRhs = static_cast<BodyMeta*>(bodyRhs->GetUserData());

	collision_handler handler = table[(int)metaLhs->type][(int)metaRhs->type];

	if (handler != nullptr)
		handler(metaLhs->link, metaRhs->link);
	else
	{
		handler = table[(int)metaRhs->type][(int)metaLhs->type];
		if (handler != nullptr)
			handler(metaRhs->link, metaLhs->link);
	}
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	HandleContactEventFor(contact, beginListenerTable);
}


void MyContactListener::EndContact(b2Contact* contact)
{
	HandleContactEventFor(contact, endListenerTable);
}


// debugDraw
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

void debugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {

}

void debugDraw::DrawTransform(const b2Transform& xf) {

}

void debugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {

}
