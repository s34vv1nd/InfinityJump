#include "stdafx.h"
#include "GSPause.h"


shared_ptr<Sprite> GSPause::m_crown = NULL;
shared_ptr<Sprite> GSPause::m_pause = NULL;
shared_ptr<Button> GSPause::m_resumeButton = NULL;
shared_ptr<Button> GSPause::m_restartButton = NULL;
shared_ptr<Button> GSPause::m_exitButton = NULL;


void GSPause::OnClickResumeButton(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
	}
}

void GSPause::OnClickRestartButton(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_PLAY);
	}
}

void GSPause::OnClickExitButton(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PopState();
	}
}

GSPause::GSPause()
{
}

GSPause::~GSPause()
{
}

void GSPause::Init() {
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(PAUSESCENE_FILE);
	if (exitcode) return;


	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "PauseTextBoard") {
				m_pause = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "CrownTextBoard") {
				m_crown = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "RESUME_BUTTON") {
				m_resumeButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPause::OnClickResumeButton);
			}
			else if (obj->getName() == "RESTART_BUTTON") {
				m_restartButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPause::OnClickRestartButton);
			}
			else if (obj->getName() == "EXIT_BUTTON") {
				m_exitButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPause::OnClickExitButton);
			}
		}
	}
}

inline void GSPause::TouchActionUp(int x, int y) {
	if (m_resumeButton->onClick(x, y, false)) return;
	if (m_restartButton->onClick(x, y, false)) return;
	if (m_exitButton->onClick(x, y, false)) return;
}

inline void GSPause::Draw() {
	Singleton<GameStateMachine>::GetInstance()->PreviousState()->Draw();
	if (m_crown) m_crown->Draw();
	if (m_pause) m_pause->Draw();
	m_resumeButton->Draw();
	m_restartButton->Draw();
	m_exitButton->Draw();
}
