#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
	mSoloud.init();
	loadSource("jumping", "../Resources/Sound/jumping.wav");
	loadSource("landing", "../Resources/Sound/landing.wav");
	loadSource("click_button", "../Resources/Sound/button.wav");
	loadSource("game_fail", "../Resources/Sound/game_fail.wav");
}


SoundManager::~SoundManager()
{
	mSoloud.deinit();
}

void SoundManager::loadSource(const char * name,const char * source)
{
	SoLoud::Wav *wav = new SoLoud::Wav();
	wav->load(source);
	mWavList.insert(std::pair<const char *, SoLoud::Wav *>(name, wav));
}

void SoundManager::playSound(const char * name)
{
	mSoloud.play(*mWavList.find(name)->second);
	while (mSoloud.getActiveVoiceCount() > 0)
	{
		SoLoud::Thread::sleep(100);
	}
}
