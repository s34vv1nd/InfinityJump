#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"


GameStateMachine::GameStateMachine()
{
	m_running = true;
	m_currentState = 0;
}

GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::Cleanup()
{
	while (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}
	m_currentState = NULL;
}

void GameStateMachine::PushState(StateType stt)
{
	std::shared_ptr<GameStateBase> state = GameStateBase::CreateState(stt);
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Pause();
	}
	m_StateStack.push_back(state);
	state->Enter();
	m_currentState = state;
}

void GameStateMachine::PopState()
{
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}

	if (!m_StateStack.empty()) {
		m_StateStack.back()->Resume();
		m_currentState = m_StateStack.back();
	}
}

std::shared_ptr<GameStateBase> GameStateMachine::CurrentState() const
{
	return m_currentState;
}

bool GameStateMachine::CountStates() const
{
	return m_StateStack.size() > 0;
}