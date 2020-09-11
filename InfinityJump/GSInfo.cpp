#include "stdafx.h"
#include "GSInfo.h"

std::shared_ptr<Sprite> GSInfo::m_background = NULL;
std::shared_ptr<Button> GSInfo::m_backmenuButton = NULL;

void GSInfo::onCLickBackMenuButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
	}
}
GSInfo::GSInfo()
{
}


GSInfo::~GSInfo()
{
}

void GSInfo::Init()
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
				m_backmenuButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSInfo::onCLickBackMenuButton);
			}
		}
	}
}

void GSInfo::Enter()
{

}
void GSInfo::Exit()
{
}

void GSInfo::Pause()
{
}

void GSInfo::Resume()
{
}

void GSInfo::Key(unsigned char key, bool isPressed)
{

}
void GSInfo::TouchActionDown(int x, int y)
{
	
}
void GSInfo::TouchActionMove(int x, int y)
{

}
void GSInfo::TouchActionUp(int x, int y)
{
	m_backmenuButton->onClick(x, y, false);

}
void GSInfo::Update(float deltaTime)
{
	
}

void GSInfo::Draw()
{
	m_background->Draw();
	m_backmenuButton->Draw();
}
