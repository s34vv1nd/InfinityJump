#pragma once
#include "Box2D/Box2D.h"
#include "Game.h"

class ContactListener :
    public b2ContactListener
{
    //void BeginContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    //void EndContact(b2Contact* contact);
};

