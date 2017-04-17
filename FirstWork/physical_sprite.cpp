#include "physical_sprite.h"
#include "world.h"
#include "renderer.h"

using namespace sf;


PhysicalSprite::PhysicalSprite(const Vector2f & pos
	, const Sprite & spriteToUse
	, BodyType bodyType
	, float boxWidth
	, float boxHeight)
	: Drawable(), sprite(spriteToUse)
{
	b2BodyDef tempBody;
	tempBody.position.Set(pos.x, pos.y);

	b2Body* tempbody = world->CreateBody(&tempBody);

	b2PolygonShape tempbox;
	//set size of ground box
	tempbox.SetAsBox(boxWidth, boxHeight);

	tempbody->CreateFixture(&tempbox, 0.0f);
	tempbody->SetUserData(new BodyMeta{ bodyType, this });

	renderer->RegisterDrawable(this);
}

PhysicalSprite::~PhysicalSprite()
{
}

void PhysicalSprite::draw(RenderTarget& target, RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// draw the vertex array
	target.draw(sprite);
}