#pragma once
#include <memory>
#include "GameStateBase.h"
#include "StatesType.h"
#include <list>

class GameStateBase;

class GameStateMachine
{
	std::vector < std::shared_ptr<GameStateBase>> m_StateStack;
	std::shared_ptr<GameStateBase> m_currentState;
	bool m_running;
	bool m_fullscreen;

public:
	GameStateMachine();
	~GameStateMachine();

	void PushState(StateType stt);
	void PopState();

	std::shared_ptr<GameStateBase> CurrentState() const;
	bool CountStates() const;
	void Cleanup();
};

