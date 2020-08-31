#pragma once
#include <queue>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "GameStateBase.h"
#include "Box2D/Box2D.h"
#include "Pad.h"
#include "Character.h"
#include "ContactListener.h"

class ContactListener;

class GSPlay : public GameStateBase
{
	static std::vector<Object*> m_objList;
	static Sprite* m_background;
	static b2World* m_world;
	static b2Body* m_groundBody;
	static AnimSprite* m_characterSprite;
	static Sprite* m_normalPadSprite;
	static Sprite* m_killerPadSprite;
	static GLfloat m_fSpawnTime;
	static ContactListener* m_contactListener;

	Character* m_character;
	std::deque<Pad*> m_pads;

	void CreateNewPad(bool canKill, int level);

public:
	GSPlay();
	~GSPlay();

	void Init();
	void Enter();
	void Pause();
	void Resume();
	void Exit();

	void Key(unsigned char key, bool bIsPressed);
	void TouchActionDown(int x, int y);
	void TouchActionUp(int x, int y);
	void TouchActionMove(int x, int y);

	void Update(float deltaTime);
	void Draw();
};

