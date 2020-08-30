#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::Initialize()
{
	m_StateType = STATE_Menu;
	Singleton<ResourceManager>::GetInstance()->Init(RM_MENU);
	Singleton<SceneManager>::GetInstance()->Init(SM_MENU);
}

void Game::Draw()
{
	Singleton<SceneManager>::GetInstance()->Draw(); 
}

void Game::SwitchStateByKey(StatesType state, unsigned char key, bool bIsPressed)
{
	switch (state)
	{
	case STATE_Menu:
		switch (key)
		{
		case 'm':
		case 'M':
			if (m_Music) {
				Singleton<ResourceManager>::GetInstance()->Init(RM_MUSIC_OFF);
				Singleton<SceneManager>::GetInstance()->Init(SM_MUSIC_OFF);
				m_Music = false;
			}
			else {
				Singleton<ResourceManager>::GetInstance()->Init(RM_MENU);
				Singleton<SceneManager>::GetInstance()->Init(SM_MENU);
				m_Music = true;
			}
			break;
		case 'h':
		case 'H':
			Singleton<ResourceManager>::GetInstance()->Init(RM_HELP);
			Singleton<SceneManager>::GetInstance()->Init(SM_HELP);
			//printf("%d \n", state);
			m_StateType = STATE_Help;
			break;
		case 'c':
		case 'C':
			Singleton<ResourceManager>::GetInstance()->Init(RM_CREDIT);
			Singleton<SceneManager>::GetInstance()->Init(SM_CREDIT);
			m_StateType = STATE_Credit;
			break;
		case 'p':
		case ' ':
			m_StateType = STATE_Play;
			Singleton<GSPlay>::GetInstance()->Render();
			Singleton<GSPlay>::GetInstance()->Play();
			break;
		}
		break;
	case STATE_Credit:
	case STATE_Help:
		if (key == 'b' || key == 'B') {
			Singleton<ResourceManager>::GetInstance()->Init(RM_MENU);
			Singleton<SceneManager>::GetInstance()->Init(SM_MENU);
			m_StateType = STATE_Menu;
		}
		break;
	case STATE_Play:
		switch (key)
		{
		case 's':
		case 'S':
			Singleton<ResourceManager>::GetInstance()->Init(RM_PAUSE);
			Singleton<SceneManager>::GetInstance()->Init(SM_PAUSE);
			m_StateType = STATE_Pause;
			break;
		}
		break;
	case STATE_Pause:
		switch (key)
		{
		case 'e':
		case 'E':
			Singleton<ResourceManager>::GetInstance()->Init(RM_MENU);
			Singleton<SceneManager>::GetInstance()->Init(SM_MENU);
			m_StateType = STATE_Menu;
			break;
		case 'r':
		case 'R':
			Singleton<ResourceManager>::GetInstance()->Init(RM_PLAY);
			Singleton<SceneManager>::GetInstance()->Init(SM_PLAY);
			m_StateType = STATE_Play;
			break;
		default:
			break;
		}
		break;
	}
}