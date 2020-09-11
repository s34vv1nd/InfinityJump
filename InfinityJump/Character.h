#pragma once
#include "..\3DEngine\AnimSprite.h"
#include "Box2D/Box2D.h"
#include "Define.h"
#include "Pad.h"
#include "CoordinateConverter.h"
#include "SoundManager.h"

class Pad;

class Character :
    public AnimSprite
{
    std::shared_ptr<b2World> m_world;
    b2Body* m_body = NULL;
    Pad* m_currentPad = NULL;
	Pad* m_previousPad = NULL;
    bool m_isOnTheGround = false;
    bool m_isJumpingFirst = false;
    bool m_isJumpingSecond = false;
    bool m_isDead = false;
    int m_iPoint = 0;
	int m_HighScore = 0;

public:
    Character(std::shared_ptr<b2World> world, std::shared_ptr<AnimSprite> obj);
    ~Character();

	GLfloat getWidth();
	GLfloat getHeight();
	void setPos2D(Vector2 pos2D);

    b2Body* getBody();
    Pad* getCurrentPad();
    void setCurrentPad(Pad* pad);
    bool isOnTheGround();
    void setIsOnTheGround(bool isOnTheGround);
    bool isJumpingFirst();
    bool isJumpingSecond();
    bool isDead();
    void die();

    int getPoint();
    void setPoint(int point);
	int getHighScore();
	void setHighScore(int score);
	void getCurrentHighScore();

    virtual void InitBody();
    virtual void Update(GLfloat dt);

    void JumpFirst();
    void JumpSecond();
};

