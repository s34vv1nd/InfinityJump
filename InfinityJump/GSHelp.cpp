#include "stdafx.h"
#include "GSHelp.h"

std::shared_ptr<Sprite> GSHelp::m_background = NULL;
std::shared_ptr<Sprite> GSHelp::m_textBoard = NULL;
std::shared_ptr<Button> GSHelp::m_backmenuButton = NULL;

void GSHelp::onCLickBackMenuButton(int x, int y, bool isPressed) {
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_MENU);
	}
}

GSHelp::GSHelp()
{
}


GSHelp::~GSHelp()
{
}
void GSHelp::Init() {
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(HELPSCENE_FILE);
	if (exitcode) return;
	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (const auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "MenuBackground") {
				m_background = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "MenuTextBoard") {
				m_textBoard = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "MENU_BUTTON_BACK") {
				m_backmenuButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSHelp::onCLickBackMenuButton);
			}
			}
		}
}
void GSHelp::Enter() {

}
void GSHelp::Exit() {

}
void GSHelp::Pause() {

}
void GSHelp::Resume() {

}
void GSHelp::Key(unsigned char key, bool isPressed) {

}
void GSHelp::TouchActionDown(int x, int y) {
	m_backmenuButton->onClick(x, y, true);
}
void GSHelp::TouchActionMove(int x, int y) {

}
void GSHelp::TouchActionUp(int x, int y) {
	m_backmenuButton->onClick(x, y, false);
}
void GSHelp::Update(float dt) {
	m_background->Update(dt);
	m_backmenuButton->Update(dt);
	m_textBoard->Update(dt);
}
void GSHelp::Draw() {
	m_background->Draw();
	m_backmenuButton->Draw();
	m_textBoard->Draw();
}