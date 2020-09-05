#include "stdafx.h"
#include "GSMenu.h"


std::shared_ptr<Sprite> GSMenu::m_background = NULL;
std::shared_ptr<Button> GSMenu::m_playButton = NULL;
std::shared_ptr<Button> GSMenu::m_helpButton = NULL;

void GSMenu::onClickPlayButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_PLAY);
	}
}

void GSMenu::onClickHelpButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_PLAY);
	}
}

GSMenu::GSMenu()
{
}

GSMenu::~GSMenu()
{
}

void GSMenu::Init()
{
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(MENUSCENE_FILE);
	if (exitcode) return;
	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (const auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "MENU_BACKGROUND") {
				m_background = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "MENU_BUTTON_START") {
				m_playButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSMenu::onClickPlayButton);
			}
			else if (obj->getName() == "MENU_BUTTON_HIGHSCORE") {
				m_helpButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSMenu::onClickHelpButton);
			}
		}
	}
}

void GSMenu::Enter()
{
}

void GSMenu::Exit()
{
}

void GSMenu::Key(unsigned char key, bool bIsPressed)
{
}

void GSMenu::TouchActionDown(int x, int y)
{
	m_playButton->onClick(x, y, true);
	m_helpButton->onClick(x, y, true);
}

void GSMenu::TouchActionMove(int x, int y)
{
}

void GSMenu::TouchActionUp(int x, int y)
{
	m_playButton->onClick(x, y, false);
	m_helpButton->onClick(x, y, false);
}

void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}

void GSMenu::Update(float dt)
{

	m_background->Update(dt); 
	m_playButton->Update(dt);
	m_helpButton->Update(dt);
}

void GSMenu::Draw()
{
	m_background->Draw();
	m_playButton->Draw();
	m_helpButton->Draw();
}
