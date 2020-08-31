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
	make_shared<GSMenu>()->Init();
	make_shared<GSPlay>()->Init();
	
	Singleton<GameStateMachine>::GetInstance()->PushState(STATE_MENU);
}

void Game::Draw()
{
	Singleton<GameStateMachine>::GetInstance()->CurrentState()->Draw();
}

void Game::Update(GLfloat dt)
{
	Singleton<GameStateMachine>::GetInstance()->CurrentState()->Update(dt);
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
