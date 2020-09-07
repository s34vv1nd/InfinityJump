#include "stdafx.h"
#include "GSMenu.h"


std::shared_ptr<Sprite> GSMenu::m_background = NULL;
std::shared_ptr<Button> GSMenu::m_playButton = NULL;
std::shared_ptr<Button> GSMenu::m_helpButton = NULL;
std::shared_ptr<Button> GSMenu::m_creditButton = NULL;
std::shared_ptr<Button> GSMenu::m_settingButton = NULL;
std::shared_ptr<Button> GSMenu::m_selectButton = NULL;

void GSMenu::onClickPlayButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_PLAY);
	}
}
void GSMenu::onClickCreditButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_CREDIT);
	}
}
void GSMenu::onClickHelpButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_HELP);
	}
}
void GSMenu::onClickSettingButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_OPTION);
	}
}

void GSMenu::onClickSelectButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_SELECT);
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
			else if (obj->getName() == "MENU_BUTTON_CREDIT") {
				m_creditButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSMenu::onClickCreditButton);
			}
			else if (obj->getName() == "MENU_BUTTON_HELP") {
				m_helpButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSMenu::onClickHelpButton);
			}
			else if (obj->getName() == "MENU_BUTTON_SETTINGS") {
				m_settingButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSMenu::onClickSettingButton);
			}
			else if (obj->getName() == "MENU_BUTTON_SELECT") {
				m_selectButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSMenu::onClickSelectButton);
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
	switch (key)
	{
	case 'C':
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_SELECT);
		break;
	default:
		break;
	}
}

void GSMenu::TouchActionDown(int x, int y)
{
	m_playButton->onClick(x, y, true);
	m_creditButton->onClick(x, y, true);
	m_helpButton->onClick(x, y, true);
	m_settingButton->onClick(x, y, true);
}

void GSMenu::TouchActionMove(int x, int y)
{
}

void GSMenu::TouchActionUp(int x, int y)
{
	m_playButton->onClick(x, y, false);
	m_creditButton->onClick(x, y, false);
	m_helpButton->onClick(x, y, false);
	m_settingButton->onClick(x, y, false);
	m_selectButton->onClick(x, y, false);
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
	m_creditButton->Update(dt);
	m_helpButton->Update(dt);
	m_settingButton->Update(dt);
	m_selectButton->Update(dt);
}

void GSMenu::Draw()
{
	m_background->Draw();
	m_playButton->Draw();
	m_creditButton->Draw();
	m_helpButton->Draw();
	m_settingButton->Draw();
	//m_selectButton->Draw();
}
