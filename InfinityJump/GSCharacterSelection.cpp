#include "stdafx.h"
#include "GSCharacterSelection.h"


std::shared_ptr<Sprite> GSCharacterSelection::m_background = NULL;
std::shared_ptr<Button> GSCharacterSelection::m_homeButton = NULL;
std::shared_ptr<Button> GSCharacterSelection::m_leftArrowButton = NULL;
std::shared_ptr<Button> GSCharacterSelection::m_rightArrowButton = NULL;

std::vector<std::shared_ptr<AnimSprite>> GSCharacterSelection::m_characterSprites = std::vector<std::shared_ptr<AnimSprite>>();
int GSCharacterSelection::m_currentCharacterSprite = 0;

void GSCharacterSelection::OnClickHomeButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_MENU);
	}
}

void GSCharacterSelection::OnClickLeftArrowButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		m_currentCharacterSprite += m_characterSprites.size() - 1;
		m_currentCharacterSprite %= m_characterSprites.size();
	}
}

void GSCharacterSelection::OnClickRightArrowButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		m_currentCharacterSprite += 1;
		m_currentCharacterSprite %= m_characterSprites.size();
	}
}

GSCharacterSelection::GSCharacterSelection()
{
}


GSCharacterSelection::~GSCharacterSelection()
{
}

std::shared_ptr<AnimSprite> GSCharacterSelection::getCurrentCharacterSprite()
{
	return m_characterSprites[m_currentCharacterSprite];
}

void GSCharacterSelection::Init() {
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(CHARACTERSELECTIONSCENE_FILE);
	if (exitcode) return;


	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (auto obj : m_objList) {
		if (obj->getName() == "BACKGROUND") {
			m_background = dynamic_pointer_cast<Sprite>(obj);
		}
		else if (obj->getName() == "BUTTON_HOME") {
			m_homeButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSCharacterSelection::OnClickHomeButton);
		}
		else if (obj->getName() == "CHARACTER") {
			m_characterSprites.push_back(dynamic_pointer_cast<AnimSprite>(obj));
		}
		else if (obj->getName() == "BUTTON_LEFTARROW") {
			m_leftArrowButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSCharacterSelection::OnClickLeftArrowButton);

		}
		else if (obj->getName() == "BUTTON_RIGHTARROW") {
			m_rightArrowButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSCharacterSelection::OnClickRightArrowButton);
		}
	}
	m_currentCharacterSprite = 0;
}

void GSCharacterSelection::TouchActionUp(int x, int y) {
	if (m_homeButton->onClick(x, y, false)) return;
	if (m_leftArrowButton->onClick(x, y, false)) return;
	if (m_rightArrowButton->onClick(x, y, false)) return;
}

inline void GSCharacterSelection::Update(float dt) {
	m_background->Update(dt);
	m_characterSprites[m_currentCharacterSprite]->Update(dt);
	m_homeButton->Update(dt);
	m_leftArrowButton->Update(dt);
	m_rightArrowButton->Update(dt);
}

inline void GSCharacterSelection::Draw() {
	m_background->Draw();
	m_characterSprites[m_currentCharacterSprite]->Draw();
	m_homeButton->Draw();
	m_leftArrowButton->Draw();
	m_rightArrowButton->Draw();
}
