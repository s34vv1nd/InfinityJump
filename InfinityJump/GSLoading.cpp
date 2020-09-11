#include "stdafx.h"
#include "GSLoading.h"


GSLoading::GSLoading()
{
}


GSLoading::~GSLoading()
{
}

void GSLoading::Init() {
}

void GSLoading::Update(float dt) {
	Singleton<TextManager>::GetInstance()->Init();
	make_shared<GSMenu>()->Init();
	make_shared<GSSelection>()->Init();
	make_shared<GSHelp>()->Init();
	make_shared<GSInfo>()->Init();
	make_shared<GSPlay>()->Init();
	make_shared<GSPause>()->Init();
	make_shared<GSGameOver>()->Init();
	make_shared<GSSound>()->Init();
	Singleton<GameStateMachine>::GetInstance()->PushState(STATE_MENU);
}

void GSLoading::Draw() {
}
