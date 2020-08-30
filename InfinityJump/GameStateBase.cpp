#include "stdafx.h"
#include "GameStateBase.h"
#include "GSMenu.h"
#include "GSPlay.h"

GameStateBase::GameStateBase()
{
}


GameStateBase::~GameStateBase()
{
}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	switch (stt) {
	case STATE_MENU:
		return std::shared_ptr<GSMenu>();
		break;
	case STATE_PLAY:
		return std::shared_ptr<GSPlay>();
		break;
	default:
		return std::shared_ptr<GameStateBase>();
	}
}
