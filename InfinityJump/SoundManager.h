#pragma once
#include <assert.h>
#include <map>
#include <thread>
#include "../Include/Soloud/soloud.h"
#include "../Include/Soloud/soloud_thread.h"
#include "../Include/Soloud/soloud_wav.h"

enum SoundType {
	JUMP,
	LAND,
	CLICK_BUTTON,
	GAME_FAIL
};

#define ON true
#define OFF false

enum SoundTrackType {
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
	void playSound(SoundType type);
	void playSoundTrack(SoundTrackType type);
	void loadSoundTrackSource(SoundTrackType type, const char * source);
	void loadSoundEffectSource(SoundType type, const char * source);
	void setVolume(float vol);
	void setMusicStatus(bool status);
	void setSoundEffectStatus(bool status);
	void setPlayingSoundTrack(SoundTrackType type);
private:
	SoLoud::Soloud mSoloud;
	SoLoud::Wav mWav;
	SoundTrackType mcPlayingSoundTrack;
	float mCurrentVolume = 1.0f;
	std::map<SoundType, SoLoud::Wav> mWavSoundEffectList;
	std::map<SoundTrackType, SoLoud::Wav> mWavSoundTrackList;
};

