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
bool GSSound::m_isMusic = false;
bool GSSound::m_isEffect = false;
int m_volumeValue = 10;

void GSSound::OnClickHomeButton(int x, int y, bool isPressed, void* context) {
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
	}
}
void GSSound::OnClickMusicOnButton(int x, int y, bool isPressed, void* context) {

}
void GSSound::OnClickMusicOffButton(int x, int y, bool isPressed, void* context) {

}
void GSSound::OnClickEffectOnButton(int x, int y, bool isPressed, void* context) {

}
void GSSound::OnClickEffectOffButton(int x, int y, bool isPressed, void* context) {

}
void GSSound::OnClickVolumeUpButton(int x, int y, bool isPressed, void* context) {

}
void GSSound::OnClickVolumeDownButton(int x, int y, bool isPressed, void* context) {

}
GSSound::GSSound()
{
}


GSSound::~GSSound()
{
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
				m_homeButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickHomeButton);
			}
			else if (obj->getName() == "MENU_BUTTON_EFFECT_ON") {
				m_effectOn = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickEffectOnButton);
			}
			else if (obj->getName() == "MENU_BUTTON_EFFECT_OFF") {
				m_effectOff = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickEffectOffButton);
			}
			else if (obj->getName() == "MENU_BUTTON_MUSIC_ON") {
				m_musicOn = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickMusicOnButton);
			}
			else if (obj->getName() == "MENU_BUTTON_MUSIC_OFF") {
				m_musicOff = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSSound::OnClickMusicOffButton);
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
	m_Volume = make_shared<Text>("VOLUME",
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(150.0f, 170.0f), Vector2(2.0f, 2.0f));
	m_texton = make_shared<Text>("ON/OFF",
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(400.0f, 450.0f), Vector2(2.0f, 2.0f));
	m_textVolume = make_shared<Text>(std::to_string(m_volumeValue), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(500.0f, 170.0f), Vector2(2.0f, 2.0f));
}
void GSSound::Pause(){}
void GSSound::Resume(){}
void GSSound::Exit(){}

void GSSound::Key(unsigned char key, bool bIsPressed){}
void GSSound::TouchActionDown(int x, int y){}
void GSSound::TouchActionMove(int x, int y){}
void GSSound::TouchActionUp(int x, int y){
	m_homeButton->onClick(x, y, false);
	if (!m_isMusic) {
		if (m_musicOn->onClick(x, y, false)) {
			Singleton<SoundManager>::GetInstance()->setMusicStatus(OFF);
			m_isMusic = true;
			return;
		}
	}
	else {
		if (m_musicOff->onClick(x, y, false)) {
			Singleton<SoundManager>::GetInstance()->setMusicStatus(ON);
			m_isMusic = false;
			return;
		}
	}
	if (!m_isEffect) {
		if (m_effectOn->onClick(x, y, false)) {
			Singleton<SoundManager>::GetInstance()->setSoundEffectStatus(OFF);
			m_isEffect = true;
			return;
		}
	}
	else {
		if (m_effectOff->onClick(x, y, false)) {
			Singleton<SoundManager>::GetInstance()->setSoundEffectStatus(ON);
			m_isEffect = false;
			return;
		}
	}
	if (m_volumeValue <= 9 && m_volumeValue >= 0) {
		if (m_volumeUp->onClick(x, y, false)) {				
			m_textVolume = make_shared<Text>(std::to_string(++m_volumeValue), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(500.0f, 170.0f), Vector2(2.0f, 2.0f));
			if (!m_isMusic) {
				if (m_volumeValue == 0) {
					Singleton<SoundManager>::GetInstance()->setVolume(0.0f);
				}
				else
					Singleton<SoundManager>::GetInstance()->setVolume(m_volumeValue * 0.1f);
			}
			return;
		}
	}
	if (m_volumeValue <= 10 && m_volumeValue >= 1) {
		if (m_volumeDown->onClick(x, y, false)) {
			m_textVolume = make_shared<Text>(std::to_string(--m_volumeValue), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(500.0f, 170.0f), Vector2(2.0f, 2.0f));
			Singleton<SoundManager>::GetInstance()->setVolume(m_volumeValue * 0.1f);
			return;
		}
	}
}

void GSSound::Update(float dt){
}

void GSSound::Draw(){
	m_background->Draw();
	m_homeButton->Draw();
	if (!m_isMusic) {
		m_musicOn->Draw();
	}
	else {
		m_musicOff->Draw();
	}
	if (!m_isEffect) {
		m_effectOn->Draw();
	}
	else {
		m_effectOff->Draw();
	}
	m_volumeUp->Draw();
	m_volumeDown->Draw();
	m_textSoundSetting->Draw();
	m_textVolume->Draw();
	m_Volume->Draw();
	m_textMusic->Draw();
	m_textEffect->Draw();
	m_texton->Draw();
}