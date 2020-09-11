#include "stdafx.h"
#include "GSGameOver.h"


shared_ptr<Button> GSGameOver::m_newGameButton = NULL;
shared_ptr<Button> GSGameOver::m_exitButton = NULL;

void GSGameOver::OnClickRestartButton(int x, int y, bool isPressed, void * context)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_PLAY);
	}
}

void GSGameOver::OnClickExitButton(int x, int y, bool isPressed, void * context)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PopState();
	}
}

GSGameOver::GSGameOver()
{
}


GSGameOver::~GSGameOver()
{
}

void GSGameOver::Init() {
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(GAMEOVERSCENE_FILE);
	if (exitcode) return;


	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "NEWGAME") {
				m_newGameButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSGameOver::OnClickRestartButton);
			}
			else if (obj->getName() == "EXIT") {
				m_exitButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSGameOver::OnClickExitButton);
			}
		}
	}
}

inline void GSGameOver::TouchActionUp(int x, int y) {
	if (m_newGameButton->onClick(x, y, false)) return;
	if (m_exitButton->onClick(x, y, false)) return;
}

inline void GSGameOver::Update(float dt) {
	static_pointer_cast<GSPlay>(Singleton<GameStateMachine>::GetInstance()->PreviousState())->UpdateWhenGameOver(dt);
}

inline void GSGameOver::Draw() {
	Singleton<GameStateMachine>::GetInstance()->PreviousState()->Draw();
	m_newGameButton->Draw();
	m_exitButton->Draw();
}
