#pragma once
#include "..\3DEngine\Sprite.h"
#include "Box2D/Box2D.h"
#include "Define.h"

class Pad :
    public Sprite
{
    b2Body* m_body;
    bool m_canKill = false;

public:
    Pad();
    Pad(b2World* world, Sprite* obj, bool canKill = false);
    ~Pad();

    b2Body* getBody();
    bool isKiller();

    virtual void InitBody(b2World* world, Vector2 pos2D, b2Vec2 velocity);
    virtual void Update(GLfloat dt);
};

