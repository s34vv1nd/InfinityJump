#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "Game.h"

class GSLoading :
	public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static bool m_done;
	//static int m_draw;
	static int m_update;

public:
	GSLoading();
	~GSLoading();

	static void setDone(bool done);

	virtual void Init();
	virtual void Enter() {}
	virtual void Exit() {}
	virtual void Pause() {}
	virtual void Resume() {}

	virtual void Key(unsigned char key, bool bIsPressed) {}
	virtual void TouchActionDown(int x, int y) {}
	virtual void TouchActionMove(int x, int y) {}
	virtual void TouchActionUp(int x, int y) {}

	virtual void Update(float dt);
	virtual void Draw();
};

