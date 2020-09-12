#include "stdafx.h"
#include "GSSelection.h"


std::shared_ptr<Button> GSSelection::m_homeButton = NULL;
std::shared_ptr<Button> GSSelection::m_leftArrowButton1 = NULL;
std::shared_ptr<Button> GSSelection::m_rightArrowButton1 = NULL;
std::shared_ptr<Button> GSSelection::m_leftArrowButton2 = NULL;
std::shared_ptr<Button> GSSelection::m_rightArrowButton2 = NULL;

std::vector<std::shared_ptr<AnimSprite>> GSSelection::m_characterSprites = std::vector<std::shared_ptr<AnimSprite>>();
int GSSelection::m_currentCharacterSprite = 0;

std::vector<std::shared_ptr<GameMap>> GSSelection::m_gameMaps = std::vector<std::shared_ptr<GameMap>>();
int GSSelection::m_currentMap = 0;


void GSSelection::OnClickHomeButton(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
	}
}

void GSSelection::OnClickLeftArrowButton1(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		m_currentCharacterSprite += m_characterSprites.size() - 1;
		m_currentCharacterSprite %= m_characterSprites.size();
	}
}

void GSSelection::OnClickRightArrowButton1(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		m_currentCharacterSprite += 1;
		m_currentCharacterSprite %= m_characterSprites.size();
	}
}

void GSSelection::OnClickLeftArrowButton2(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		m_currentMap += m_gameMaps.size() - 1;
		m_currentMap %= m_gameMaps.size();
		switch (m_currentMap)
		{
		case 0:
			Singleton<SoundManager>::GetInstance()->setCurrentBGM(SOUND_TRACK1);
			break;
		case 1:
			Singleton<SoundManager>::GetInstance()->setCurrentBGM(SOUND_TRACK2);
			break;
		case 2:
			Singleton<SoundManager>::GetInstance()->setCurrentBGM(SOUND_TRACK3);
			break;
		case 3:
			Singleton<SoundManager>::GetInstance()->setCurrentBGM(SOUND_TRACK4);
			break;
		default:
			break;
		}
	}
}

void GSSelection::OnClickRightArrowButton2(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		m_currentMap += 1;
		m_currentMap %= m_gameMaps.size();
		switch (m_currentMap)
		{
		case 0:
			Singleton<SoundManager>::GetInstance()->setCurrentBGM(SOUND_TRACK1);
			break;
		case 1:
			Singleton<SoundManager>::GetInstance()->setCurrentBGM(SOUND_TRACK2);
			break;
		case 2:
			Singleton<SoundManager>::GetInstance()->setCurrentBGM(SOUND_TRACK3);
			break;
		case 3:
			Singleton<SoundManager>::GetInstance()->setCurrentBGM(SOUND_TRACK4);
			break;
		default:
			break;
		}
	}
}

GSSelection::GSSelection()
{
}


GSSelection::~GSSelection()
{
}

std::shared_ptr<AnimSprite> GSSelection::getCurrentCharacterSprite()
{
	return m_characterSprites[m_currentCharacterSprite];
}

std::shared_ptr<GameMap> GSSelection::getCurrentMap()
{
	return m_gameMaps[m_currentMap];
}

void GSSelection::Init() {
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(SELECTIONSCENE_FILE);
	if (exitcode) return;

	std::vector<std::shared_ptr<Sprite>> backgroundSprites;
	std::vector<std::shared_ptr<Sprite>> normalPadSprites;
	std::vector<std::shared_ptr<Sprite>> killerPadSprites;

	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (auto obj : m_objList) {
		if (obj->getName() == "BUTTON_HOME") {
			m_homeButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSelection::OnClickHomeButton);
		}
		else if (obj->getName() == "CHARACTER") {
			m_characterSprites.push_back(dynamic_pointer_cast<AnimSprite>(obj));
		}
		else if (obj->getName() == "MAP_BACKGROUND") {
			backgroundSprites.push_back(dynamic_pointer_cast<Sprite>(obj));
		}
		else if (obj->getName() == "PAD_NORMAL") {
			normalPadSprites.push_back(dynamic_pointer_cast<Sprite>(obj));
		}
		else if (obj->getName() == "PAD_KILLER") {
			killerPadSprites.push_back(dynamic_pointer_cast<Sprite>(obj));
		}
		else if (obj->getName() == "BUTTON_LEFTARROW1") {
			m_leftArrowButton1 = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSelection::OnClickLeftArrowButton1);
		}
		else if (obj->getName() == "BUTTON_RIGHTARROW1") {
			m_rightArrowButton1 = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSelection::OnClickRightArrowButton1);
		}
		else if (obj->getName() == "BUTTON_LEFTARROW2") {
			m_leftArrowButton2 = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSelection::OnClickLeftArrowButton2);
		}
		else if (obj->getName() == "BUTTON_RIGHTARROW2") {
			m_rightArrowButton2 = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSelection::OnClickRightArrowButton2);
		}
	}

	for (int i = 0; i < backgroundSprites.size(); ++i) {
		m_gameMaps.push_back(make_shared<GameMap>(
				backgroundSprites[i],
				normalPadSprites[i],
				killerPadSprites[i]
			));
	}

	m_currentCharacterSprite = 0;
	m_currentMap = 0;
}

void GSSelection::Enter() {
	for (auto& character : m_characterSprites) {
		for (auto& anim : character->getAnimations()) {
			anim->setCurrentFrame(0);
		}
		character->setCurrentAnimation(0);
	}
}

void GSSelection::TouchActionUp(int x, int y) {
	if (m_homeButton->onClick(x, y, false)) return;
	if (m_leftArrowButton1->onClick(x, y, false)) return;
	if (m_rightArrowButton1->onClick(x, y, false)) return;
	if (m_leftArrowButton2->onClick(x, y, false)) return;
	if (m_rightArrowButton2->onClick(x, y, false)) return;
}

inline void GSSelection::Update(float dt) {
	m_characterSprites[m_currentCharacterSprite]->Update(dt);
	m_homeButton->Update(dt);
	m_leftArrowButton1->Update(dt);
	m_rightArrowButton1->Update(dt);
	m_leftArrowButton2->Update(dt);
	m_rightArrowButton2->Update(dt);
}

inline void GSSelection::Draw() {
	m_gameMaps[m_currentMap]->getBackgroundSprite()->Draw();
	m_gameMaps[m_currentMap]->getNormalPadSprite()->Draw();
	m_gameMaps[m_currentMap]->getKillerPadSprite()->Draw();
	m_characterSprites[m_currentCharacterSprite]->Draw();
	m_homeButton->Draw();
	m_leftArrowButton1->Draw();
	m_rightArrowButton1->Draw();
	m_leftArrowButton2->Draw();
	m_rightArrowButton2->Draw();
}
