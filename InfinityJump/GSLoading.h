#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "Character.h"
#include "Pad.h"
#include "ContactListener.h"
#include "GSPlay.h"
#include "GSPause.h"
#include "GSGameOver.h"
#include "GSMenu.h"
#include "GSInfo.h"
#include "GSHelp.h"
#include "GSSelection.h"
#include "GSSound.h"

class GSLoading :
	public GameStateBase
{
public:
	GSLoading();
	~GSLoading();

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

