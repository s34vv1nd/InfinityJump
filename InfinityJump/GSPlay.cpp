#include "stdafx.h"
#include "GSPlay.h"


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}

void GSPlay::Render()
{
	Singleton<ResourceManager>::GetInstance()->Init(RM_PLAY);
	Singleton<SceneManager>::GetInstance()->Init(SM_PLAY);
	Singleton<SceneManager>::GetInstance()->Draw();
}

void GSPlay::Play()
{

}

void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}

void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
}

void GSPlay::Draw()
{
}
