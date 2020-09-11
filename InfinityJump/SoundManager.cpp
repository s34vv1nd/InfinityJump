#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
	mSoloud.init();
	loadSoundEffectSource(JUMP, "../Resources/Sound/jumping.wav");
	loadSoundEffectSource(LAND, "../Resources/Sound/landing.wav");
	loadSoundEffectSource(CLICK_BUTTON, "../Resources/Sound/button.wav");
	loadSoundEffectSource(GAME_FAIL, "../Resources/Sound/game_fail1.wav");
	loadSoundTrackSource(SOUND_TRACK1, "../Resources/Sound/soundtrack1.wav");
	loadSoundTrackSource(SOUND_TRACK2, "../Resources/Sound/soundtrack2.wav");
	loadSoundTrackSource(SOUND_TRACK3, "../Resources/Sound/soundtrack3.wav");
	loadSoundTrackSource(SOUND_TRACK4, "../Resources/Sound/soundtrack4.wav");
}


SoundManager::~SoundManager()
{
	mSoloud.deinit();
}

void SoundManager::loadSoundEffectSource(SoundType type, const char * source)
{
	assert(mWavSoundEffectList.find(type) == mWavSoundEffectList.end());
	mWavSoundEffectList[type] = SoLoud::Wav();
	mWavSoundEffectList[type].load(source);
}

void SoundManager::loadSoundTrackSource(SoundTrackType type, const char * source)
{
	assert(mWavSoundTrackList.find(type) == mWavSoundTrackList.end());
	mWavSoundTrackList[type] = SoLoud::Wav();
	mWavSoundTrackList[type].load(source);
	mWavSoundTrackList[type].setLooping(true);
}


void SoundManager::playSound(SoundType type)
{
	assert(mWavSoundEffectList.find(type) != mWavSoundEffectList.end());
	mSoloud.play(mWavSoundEffectList[type]);
}

void SoundManager::playSoundTrack(SoundTrackType type)
{
	assert(mWavSoundTrackList.find(type) != mWavSoundTrackList.end());
	mSoloud.playBackground(mWavSoundTrackList[type]);
	mcPlayingSoundTrack = type;
}

void SoundManager::setVolume(float vol)
{
	mSoloud.setGlobalVolume(vol);
	mCurrentVolume = vol;
}

void SoundManager::setMusicStatus(bool status)
{
	assert(mWavSoundTrackList.find(mcPlayingSoundTrack) != mWavSoundTrackList.end());
	if (!status)
		mSoloud.stopAudioSource(mWavSoundTrackList[mcPlayingSoundTrack]);
	else
		mSoloud.play(mWavSoundTrackList[mcPlayingSoundTrack]);
}

void SoundManager::setPlayingSoundTrack(SoundTrackType type)
{
	assert(mWavSoundTrackList.find(mcPlayingSoundTrack) != mWavSoundTrackList.end());
	mSoloud.stopAudioSource(mWavSoundTrackList[mcPlayingSoundTrack]);
	playSoundTrack(type);
}

void SoundManager::setSoundEffectStatus(bool status)
{
	std::map<SoundType, SoLoud::Wav>::iterator iterator;
	if (!status) {
		for (iterator = mWavSoundEffectList.begin(); iterator != mWavSoundEffectList.end(); iterator++)
			iterator->second.setVolume(0.0f);
	}
	else
	{
		for (iterator = mWavSoundEffectList.begin(); iterator != mWavSoundEffectList.end(); iterator++)
			iterator->second.setVolume(mCurrentVolume);
	}
}