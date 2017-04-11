#pragma once

enum BodyType
{
	BODY_GROUND
	, BODY_AVATAR
	, BODY_ZOMBIE
	, BODY_WALL
};

struct BodyMeta
{
	BodyType type;
	void* link;
};

