#pragma once
#include<vector>
#include<map>
#include<algorithm>
#include<memory>
#include "../3DEngine/3DEngine.h"
#include "Box2D\Box2D.h"

using namespace std;

struct PhysicsElements {

};

class PhysicsManager
{
	shared_ptr<b2World> m_world;
	

public:
	PhysicsManager();
	~PhysicsManager();
};

