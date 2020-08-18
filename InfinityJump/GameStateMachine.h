#pragma once
#include <memory>
#include "GameStateBase.h"
#include "StatesType.h"
#include <list>

class GameStateBase;

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();
	void CLeanup();
	void ChangeState(StatesType stt);
	void ChangeState(std::shared_ptr<GameStateBase> state);
	void PushState(StatesType stt);
	void PopState();
	void PerformStateChange();

	inline std::shared_ptr<GameStateBase> CurrentState() const
	{
		return m_pActiveState;
	}
	inline bool NeedsToChangeState() const
	{
		return (m_pNextState != 0);
	}
	inline bool HasState()const
	{
		return m_StatesStack.size() > 0;
	}
private:
	std::list < std::shared_ptr<GameStateBase>> m_StatesStack;
	std::shared_ptr<GameStateBase> m_pActiveState;
	std::shared_ptr<GameStateBase> m_pNextState;
	bool m_running;
	bool m_fullscreen;
};

