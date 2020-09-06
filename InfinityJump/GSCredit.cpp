#include "stdafx.h"
#include "GSCredit.h"

std::shared_ptr<Sprite> GSCredit::m_background = NULL;
std::shared_ptr<Button> GSCredit::m_backmenuButton = NULL;

void GSCredit::onCLickBackMenuButton(int x, int y, bool isPressed) {
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_MENU);
	}
}
GSCredit::GSCredit()
{
}


GSCredit::~GSCredit()
{
}

void GSCredit::Init()
{
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(CREDITSCENE_FILE);
	if (exitcode) return;
	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (const auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "MenuBackground") {
				m_background = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "MenuButtonBack") {
				m_backmenuButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSCredit::onCLickBackMenuButton);
			}
		}
	}
}

void GSCredit::Enter()
{

}
void GSCredit::Exit()
{
}

void GSCredit::Pause()
{
}

void GSCredit::Resume()
{
}

void GSCredit::Key(unsigned char key, bool isPressed)
{

}
void GSCredit::TouchActionDown(int x, int y)
{
	m_backmenuButton->onClick(x, y, true);
}
void GSCredit::TouchActionMove(int x, int y)
{

}
void GSCredit::TouchActionUp(int x, int y)
{
	m_backmenuButton->onClick(x, y, false);

}
void GSCredit::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	m_backmenuButton->Update(deltaTime);
}

void GSCredit::Draw()
{
	m_background->Draw();
	m_backmenuButton->Draw();
}
