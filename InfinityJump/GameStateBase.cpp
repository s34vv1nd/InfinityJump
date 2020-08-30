#include "stdafx.h"
#include "GameStateBase.h"
#include "GSMenu.h"
#include "GSCredit.h"
#include "GSHighScore.h"
#include "GSOption.h"
#include "GSPause.h"
#include "GSPlay.h"
#include "GSWelcom.h"
GameStateBase::GameStateBase()
{
}


GameStateBase::~GameStateBase()
{
}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StatesType stt)
{
	//std::shared_ptr<GameStateBase> gs = nullptr;
	//switch (stt)
	//{
	//case STATE_None:
	//	break;
	//case STATE_Menu:
	//	gs = std::make_shared<GSMenu>();
	//	break;
	//case STATE_Play:
	//	gs = std::make_shared<GSPlay>();
	//	break;
	//case STATE_Help:
	//	gs = std::make_shared<GSOption>();
	//	break;
	//case STATE_HighScore:
	//	gs = std::make_shared<GSHighScore>();
	//	break;
	//case STATE_Pause:
	//	gs = std::make_shared<GSPause>();
	//	break;
	//case STATE_Welcome:
	//	gs = std::make_shared<GSWelcom>();
	//	break;
	//case STATE_Credit:
	//	gs = std::make_shared<GSCredit>();
	//	break;
	//default:
	//	break;
	//}
	//return gs;
	return std::shared_ptr<GameStateBase>();
}
