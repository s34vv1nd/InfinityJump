#include "stdafx.h"
#include "GameStateBase.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "GSCredit.h"
#include "GSHelp.h"

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
		return std::make_shared<GSMenu>();
		break;
	case STATE_PLAY:
		return std::make_shared<GSPlay>();
		break;
	case STATE_HELP:
		return std::make_shared<GSHelp>();
	case STATE_CREDIT:
		return std::make_shared<GSCredit>();
	default:
		return std::make_shared<GameStateBase>();
	}
}
