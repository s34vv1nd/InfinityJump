#pragma once
#include <assert.h>
#include <map>
#include <thread>
#include "../Include/Soloud/soloud.h"
#include "../Include/Soloud/soloud_thread.h"
#include "../Include/Soloud/soloud_wav.h"

enum SFXType {
	JUMP,
	LAND,
	CLICK_BUTTON,
	GAME_FAIL
};

enum BGMType {
	SOUND_TRACK1,
	SOUND_TRACK2,
	SOUND_TRACK3,
	SOUND_TRACK4,
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void loadSFX(SFXType type, const char* source);
	void loadBGM(BGMType type, const char* source);
	void playSFX(SFXType type);
	void playBGM(BGMType type);
	void setSFXVolume(float vol);
	void setBGMVolume(float vol);
	void setBGMisON(bool status);
	void setSFXisON(bool status);
	void setCurrentBGM(BGMType type);

private:
	SoLoud::Soloud mSoloud;
	BGMType m_currentBGM;
	SoLoud::handle m_currentBGMhandle;
	float m_SFXVolume = 1.0f;
	float m_BGMVolume = 1.0f;
	bool m_SFXisON = true;
	bool m_BGMisON = true;
	std::map<SFXType, SoLoud::Wav> mSFXList;
	std::map<BGMType, SoLoud::Wav> mBGMList;
};

