#include "stdafx.h"
#include "GameStateBase.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "GSPause.h"
#include "GSInfo.h"
#include "GSHelp.h"
#include "GSSelection.h"
#include "GSGameOver.h"
#include "GSSound.h"
#include "GSLoading.h"



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
	case STATE_HELP:
		return std::make_shared<GSHelp>();
	case STATE_INFO:
		return std::make_shared<GSInfo>();
	case STATE_SOUND:
		return std::make_shared<GSSound>();
	case STATE_SELECT:
		return std::make_shared<GSSelection>();
	case STATE_PLAY:
		return std::make_shared<GSPlay>();
	case STATE_PAUSE:
		return std::make_shared<GSPause>();
	case STATE_GAMEOVER:
		return std::make_shared<GSGameOver>();
	case STATE_LOADING:
		return std::make_shared<GSLoading>();
	default:
		return std::make_shared<GameStateBase>();
	}
}
