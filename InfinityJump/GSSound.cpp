#include "stdafx.h"
#include "GSSound.h"

std::shared_ptr<Sprite> GSSound::m_background = NULL;
std::shared_ptr<Button> GSSound::m_musicOn = NULL;
std::shared_ptr<Button> GSSound::m_musicOff = NULL;
std::shared_ptr<Button> GSSound::m_effectOn = NULL;
std::shared_ptr<Button> GSSound::m_effectOff = NULL;
std::shared_ptr<Button> GSSound::m_volumeUp = NULL;
std::shared_ptr<Button> GSSound::m_volumeDown = NULL;
std::shared_ptr<Button> GSSound::m_homeButton = NULL;
bool GSSound::m_BGMisON = true;
bool GSSound::m_SFXisON = true;
int GSSound::m_volume = 10;

void GSSound::OnClickBackButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
	}
}

void GSSound::OnClickBGMOnButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		m_BGMisON = false;
		Singleton<SoundManager>::GetInstance()->setBGMisON(m_BGMisON);
	}
}

void GSSound::OnClickBGMOffButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		m_BGMisON = true;
		Singleton<SoundManager>::GetInstance()->setBGMisON(m_BGMisON);
	}
}

void GSSound::OnClickSFXOnButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		m_SFXisON = false;
		Singleton<SoundManager>::GetInstance()->setSFXisON(m_SFXisON);
	}
}

void GSSound::OnClickSFXOffButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		m_SFXisON = true;
		Singleton<SoundManager>::GetInstance()->setSFXisON(m_SFXisON);
	}
}

void GSSound::OnClickVolumeUpButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		if (m_volume < MAX_VOLUME) {
			m_volume++;
		}
	}
}

void GSSound::OnClickVolumeDownButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		if (m_volume > MIN_VOLUME) {
			m_volume--;
		}
	}
}

GSSound::GSSound()
{
}

GSSound::~GSSound()
{
}

bool GSSound::getSFXisON()
{
	return m_SFXisON;
}

bool GSSound::getBGMisON()
{
	return m_BGMisON;
}

void GSSound::Init(){
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(SOUNDSCENE_FILE);
	if (exitcode) return;
	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (const auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "MENU_BACKGROUND") {
				m_background = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "MENU_BUTTON_HOME") {
				m_homeButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickBackButton);
			}
			else if (obj->getName() == "MENU_BUTTON_EFFECT_ON") {
				m_effectOn = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickSFXOnButton);
			}
			else if (obj->getName() == "MENU_BUTTON_EFFECT_OFF") {
				m_effectOff = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickSFXOffButton);
			}
			else if (obj->getName() == "MENU_BUTTON_MUSIC_ON") {
				m_musicOn = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickBGMOnButton);
			}
			else if (obj->getName() == "MENU_BUTTON_MUSIC_OFF") {
				m_musicOff = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickBGMOffButton);
			}
			else if (obj->getName() == "MENU_BUTTON_VOLUME_UP") {
				m_volumeUp = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickVolumeUpButton);
			}
			else if (obj->getName() == "MENU_BUTTON_VOLUME_DOWN") {
				m_volumeDown = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickVolumeDownButton);
			}
		}
	}
}

void GSSound::Enter(){
	m_textSoundSetting = make_shared<Text>("SOUND SETTINGS" ,
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(290.0f, 550.0f), Vector2(2.0f, 2.0f));
	m_textMusic = make_shared<Text>("MUSIC",
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(150.0f, 370.0f), Vector2(2.0f, 2.0f));
	m_textEffect = make_shared<Text>("SFX",
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(150.0f, 270.0f), Vector2(2.0f, 2.0f));
	m_textVolume1 = make_shared<Text>("VOLUME",
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(150.0f, 170.0f), Vector2(2.0f, 2.0f));
	m_texton = make_shared<Text>("ON/OFF",
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(400.0f, 450.0f), Vector2(2.0f, 2.0f));
	m_textVolume = make_shared<Text>(std::to_string(m_volume), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(500.0f, 170.0f), Vector2(2.0f, 2.0f));
}

void GSSound::TouchActionUp(int x, int y) {
	if (m_homeButton->onClick(x, y, false)) return;

	if (m_BGMisON) {
		if (m_musicOn->onClick(x, y, false)) {
			return;
		}
	}
	else {
		if (m_musicOff->onClick(x, y, false)) {
			return;
		}
	}

	if (m_SFXisON) {
		if (m_effectOn->onClick(x, y, false)) {
			return;
		}
	}
	else {
		if (m_effectOff->onClick(x, y, false)) {
			return;
		}
	}

	if (m_volume < MAX_VOLUME && m_volume >= MIN_VOLUME) {
		if (m_volumeUp->onClick(x, y, false)) {
			return;
		}
	}

	if (m_volume <= MAX_VOLUME && m_volume > MIN_VOLUME) {
		if (m_volumeDown->onClick(x, y, false)) {
			return;
		}
	}
}

void GSSound::Update(float dt){
	Singleton<SoundManager>::GetInstance()->setBGMVolume(m_volume * 1.0f / MAX_VOLUME);
	Singleton<SoundManager>::GetInstance()->setSFXVolume(m_volume * 1.0f / MAX_VOLUME);
	m_textVolume->setText(to_string(m_volume));
}

void GSSound::Draw(){
	m_background->Draw();
	m_homeButton->Draw();
	if (m_BGMisON) {
		m_musicOn->Draw();
	}
	else {
		m_musicOff->Draw();
	}
	if (m_SFXisON) {
		m_effectOn->Draw();
	}
	else {
		m_effectOff->Draw();
	}
	m_volumeUp->Draw();
	m_volumeDown->Draw();
	m_textSoundSetting->Draw();
	m_textVolume->Draw();
	m_textVolume1->Draw();
	m_textMusic->Draw();
	m_textEffect->Draw();
	m_texton->Draw();
}