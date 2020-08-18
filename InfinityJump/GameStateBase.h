#pragma once
#include "../3DEngine/3DEngine.h"
#include "GameStateMachine.h"
#include <memory>
#include "StatesType.h"

enum StatesType;

class GameStateBase
{
public:
	GameStateBase(void);
	virtual ~GameStateBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void HandleEvents() = 0;
	virtual void HandleKeyEvents(int key, bool bIsPressed) = 0;
	virtual void HandleTouchEvents(int x, int y, bool bIsPressed) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	static std::shared_ptr<GameStateBase> CreateState(StatesType stt);
};
