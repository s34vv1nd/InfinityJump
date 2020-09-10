#pragma once
#include <map>
#include "../Include/Soloud/soloud.h"
#include "../Include/Soloud/soloud_thread.h"
#include "../Include/Soloud/soloud_wav.h"

#define JUMP "jumping"
#define LAND "landing"
#define CLICK_BUTTON "click_button"
#define GAME_FAIL "game_fail"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void playSound(const char *);
	void loadSource(const char * name, const char * source);
private:
	SoLoud::Soloud mSoloud;
	SoLoud::Wav mWav;
	std::map<const char *, SoLoud::Wav *> mWavList;
};

