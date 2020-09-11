#pragma once
#include <memory>
#include "..\3DEngine\Sprite.h"
#include "Box2D/Box2D.h"
#include "Define.h"
#include "GameStateMachine.h"
#include "GSPlay.h"
#include "Character.h"
#include "CoordinateConverter.h"

class Character;

class Pad :
    public Sprite
{
    shared_ptr<b2World> m_world;
    b2Body* m_body;
    bool m_canKill = false;
    int m_iLevel = 0;
    bool m_passedCharacter = false;
    bool m_isInUse = false;

public:
    Pad(std::shared_ptr<b2World> world, shared_ptr<Sprite> obj, bool canKill = false, int level = 0);
    ~Pad();

    b2Body* getBody();
    bool isKiller();

	void setLevel(int level);
    int getLevel();

    virtual void setPos2D(Vector2 pos2D);

    bool isBehindCharacter(shared_ptr<Character> character);
    bool getPassedCharacter();
    void setPassedCharacter(bool passed);

    bool getInUse();
    void setInUse(bool inUse);

    virtual void InitBody(Vector2 pos2D, b2Vec2 velocity);
    virtual void Update(GLfloat dt);
};

