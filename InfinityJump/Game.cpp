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
	Singleton<GSPlay>::GetInstance()->Init();
	Singleton<GSPlay>::GetInstance()->Enter();
}

void Game::Draw()
{
	Singleton<GSPlay>::GetInstance()->Draw();
}

void Game::Update(GLfloat dt)
{
	Singleton<GSPlay>::GetInstance()->Update(dt);
}

void Game::Key(unsigned char key, bool bIsPressed)
{
	Singleton<GSPlay>::GetInstance()->Key(key, bIsPressed);
}

void Game::TouchActionDown(int x, int y)
{
	
}

void Game::TouchActionUp(int x, int y)
{
}

void Game::TouchActionMove(int x, int y)
{
}

void Game::CleanUp()
{
}
