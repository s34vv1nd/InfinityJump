#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
	mSoloud.init();
	loadSFX(JUMP,			"../Resources/Sound/jumping3.wav");
	loadSFX(LAND,			"../Resources/Sound/landing.wav");
	loadSFX(CLICK_BUTTON,	"../Resources/Sound/button.wav");
	loadSFX(GAME_FAIL,		"../Resources/Sound/gameover2.wav");
	loadBGM(SOUND_TRACK1,	"../Resources/Sound/soundtrack1.wav");
	loadBGM(SOUND_TRACK2,	"../Resources/Sound/soundtrack2.wav");
	loadBGM(SOUND_TRACK3,	"../Resources/Sound/soundtrack3.wav");
	loadBGM(SOUND_TRACK4,	"../Resources/Sound/soundtrack4.wav");
}

SoundManager::~SoundManager()
{
	mSoloud.deinit();
}

void SoundManager::loadSFX(SFXType type, const char * source)
{
	assert(mSFXList.find(type) == mSFXList.end());
	mSFXList[type] = SoLoud::Wav();
	mSFXList[type].load(source);
}

void SoundManager::loadBGM(BGMType type, const char * source)
{
	assert(mBGMList.find(type) == mBGMList.end());
	mBGMList[type] = SoLoud::Wav();
	mBGMList[type].load(source);
	mBGMList[type].setLooping(true);
}

void SoundManager::playSFX(SFXType type)
{
	assert(mSFXList.find(type) != mSFXList.end());
	if (m_SFXisON)
		mSoloud.play(mSFXList[type], m_SFXVolume);
}

void SoundManager::playBGM(BGMType type)
{
	assert(mBGMList.find(type) != mBGMList.end());
	if (m_BGMisON) {
		m_currentBGMhandle = mSoloud.playBackground(mBGMList[type], m_BGMVolume);
		m_currentBGM = type;
	}
}

void SoundManager::setSFXVolume(float vol)
{
	m_SFXVolume = vol;
}

void SoundManager::setBGMVolume(float vol)
{
	if (m_BGMVolume == vol) return;
	m_BGMVolume = vol;
	mSoloud.setVolume(m_currentBGMhandle, vol);
}

void SoundManager::setSFXisON(bool status)
{
	m_SFXisON = status;
}

void SoundManager::setBGMisON(bool status)
{
	if (m_BGMisON == status) return;
	m_BGMisON = status;
	if (status) {
		playBGM(m_currentBGM);
	}
	else {
		mSoloud.stopAudioSource(mBGMList[m_currentBGM]);
	}
}

void SoundManager::setCurrentBGM(BGMType type)
{
	assert(mBGMList.find(m_currentBGM) != mBGMList.end());
	mSoloud.stopAudioSource(mBGMList[m_currentBGM]);
	playBGM(type);
}