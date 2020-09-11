#pragma once
#include "../3DEngine/3DEngine.h"
#include "GameStateMachine.h"
#include <memory>
#include "StatesType.h"


enum StateType;

class GameStateBase
{
protected:
	bool m_isPaused = false;

public:
	GameStateBase(void);
	virtual ~GameStateBase();

	virtual void Init() {}
	virtual void Enter() {}
	virtual void Exit() {}
	virtual void Pause() {}
	virtual void Resume() {}

	virtual void Key(unsigned char key, bool bIsPressed) {}
	virtual void TouchActionDown(int x, int y) {}
	virtual void TouchActionMove(int x, int y) {}
	virtual void TouchActionUp(int x, int y) {}

	virtual void Update(float dt) {}
	virtual void Draw() {}

	static std::shared_ptr<GameStateBase> CreateState(StateType stt);
};
