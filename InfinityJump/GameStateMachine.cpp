#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"


GameStateMachine::GameStateMachine()
{
	m_running = true;
	m_pActiveState = 0;
	m_pNextState = 0;
}

GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::CLeanup()
{
	while (!m_StatesStack.empty()) {
		m_StatesStack.back()->Exit();
		m_StatesStack.pop_back();
	}
}

void GameStateMachine::ChangeState(StatesType stt)
{
	std::shared_ptr<GameStateBase> gstb = GameStateBase::CreateState(stt);
	ChangeState(gstb);
}

void GameStateMachine::ChangeState(std::shared_ptr<GameStateBase> state)
{
	m_pNextState = state;
}

void GameStateMachine::PushState(StatesType stt)
{
	std::shared_ptr<GameStateBase> state = GameStateBase::CreateState(stt);
	if (!m_StatesStack.empty()) {
		m_StatesStack.back()->Pause();
	}
	m_pNextState = state;
}

void GameStateMachine::PopState()
{
	if (!m_StatesStack.empty()) {
		m_StatesStack.back()->Exit();
		m_StatesStack.pop_back();
	}

	if (!m_StatesStack.empty()) {
		m_StatesStack.back()->Resume();
	}
}

void GameStateMachine::PerformStateChange()
{
	if (m_pNextState != 0)
	{
		if (!m_StatesStack.empty()) {
			m_StatesStack.back()->Exit();
		}
		m_StatesStack.push_back(m_pNextState);
		m_StatesStack.back()->Init();
		m_pActiveState = m_pNextState;
	}
	m_pNextState = 0;
}