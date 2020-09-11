#pragma once
#include "../3DEngine/3DEngine.h"
#include "Box2D\Box2D.h"


class CoordinateConverter
{
public:
	CoordinateConverter();
	~CoordinateConverter();

	static Vector2 to_glcoord(b2Body& body);
	static b2Vec2 to_b2coord(Sprite* sprite);
};

