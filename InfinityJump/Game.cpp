#include "stdafx.h"
#include "Game.h"
#include "../3DEngine/AnimSprite.h"


Game::Game()
{
}

Game::~Game()
{
	CleanUp();
}

void Game::Init()
{
	Singleton<ResourceManager>::GetInstance()->Init(RM_TXT_FILE);
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
	//Singleton<GameStateMachine>::GetInstance()->PushState(STATE_LOADING);
}

void Game::DrawLoadingScreen()
{

}

void Game::Draw()
{
	//printf("Draw\n");
	auto& state = Singleton<GameStateMachine>::GetInstance()->CurrentState();
	if (state) {
		state->Draw();
	}
	else {

	}
}

void Game::Update(GLfloat dt)
{
	//printf("Update\n");
	auto& state = Singleton<GameStateMachine>::GetInstance()->CurrentState();
	if (state) {
		state->Update(dt);
	}
	else {

	}
}

void Game::Key(unsigned char key, bool bIsPressed)
{
	Singleton<GameStateMachine>::GetInstance()->CurrentState()->Key(key, bIsPressed);
}

void Game::TouchActionDown(int x, int y)
{
	Singleton<GameStateMachine>::GetInstance()->CurrentState()->TouchActionDown(x, y);
}

void Game::TouchActionUp(int x, int y)
{
	Singleton<GameStateMachine>::GetInstance()->CurrentState()->TouchActionUp(x, y);
}

void Game::TouchActionMove(int x, int y)
{
	Singleton<GameStateMachine>::GetInstance()->CurrentState()->TouchActionMove(x, y);
}

void Game::CleanUp()
{
}
