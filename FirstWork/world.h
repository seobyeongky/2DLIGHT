#pragma once

#include <Box2D\Box2D.h>

#include "body_meta.h"

extern b2World* world;

typedef void(*collision_handler)(void* lhs, void* rhs);

void CreateWorld();
void OnBeginContact(BodyType typeLhs, BodyType typeRhs, collision_handler handler);
void OnEndContact(BodyType typeLhs, BodyType typeRhs, collision_handler handler);