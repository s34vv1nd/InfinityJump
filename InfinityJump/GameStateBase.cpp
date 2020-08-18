#include "stdafx.h"
#include "GameStateBase.h"


GameStateBase::GameStateBase()
{
}


GameStateBase::~GameStateBase()
{
}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StatesType stt)
{
	return std::shared_ptr<GameStateBase>();
}
