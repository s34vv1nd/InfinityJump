#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 normal;
	Vector3 binormal;
	Vector3 tangent;
	Vector2 uv;
};