#include "stdafx.h"
#include "CoordinateConverter.h"
#include "../3DEngine/Sprite.h"
#include "Character.h"
#include "Pad.h"

CoordinateConverter::CoordinateConverter()
{
}


CoordinateConverter::~CoordinateConverter()
{
}

Vector2 CoordinateConverter::to_glcoord(b2Body & body)
{
	Sprite* sprite = NULL;
	if (body.GetType() == b2_dynamicBody)
		sprite = static_cast<Character*>(body.GetUserData());
	else if (body.GetType() == b2_kinematicBody)
		sprite = static_cast<Pad*>(body.GetUserData());
	else
		return{ 0, 0 };
	float x = body.GetPosition().x;
	float y = body.GetPosition().y;
	float w = sprite->getHitbox().x;
	float h = sprite->getHitbox().y;
	auto res = Vector2(
		x * 100.0f - w / 2.0f,
		y * 100.0f + h / 2.0f
	);
	return res;
}

b2Vec2 CoordinateConverter::to_b2coord(Sprite* sprite)
{
	float x = sprite->getPos2D().x;
	float y = sprite->getPos2D().y;
	float w = sprite->getHitbox().x;
	float h = sprite->getHitbox().y;
	return b2Vec2(
		(x + w / 2.0f) / 100.0f,
		(y - h / 2.0f) / 100.0f
	);
}
