#pragma once
#include <memory>
#include "Define.h"
#include "GameStateBase.h"
#include "Button.h"
#include "Text.h"
#include "SoundManager.h"

class GSMenu : public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static shared_ptr<Button> m_playButton;
	static shared_ptr<Button> m_helpButton;
	static shared_ptr<Button> m_creditButton;
	static shared_ptr<Button> m_musicOnButton;
	static shared_ptr<Button> m_musicOffButton;
	static shared_ptr<Button> m_selectButton;
	static void onClickHelpButton(int x, int y, bool isPressed, void* context);
	static void onClickCreditButton(int x, int y, bool isPressed, void* context);
	static void onClickPlayButton(int x, int y, bool isPressed, void* context);
	static void onClickMusicOnButton(int x, int y, bool isPressed, void* context);
	static void onClickSelectButton(int x, int y, bool isPressed, void* context);

public:
	GSMenu();
	~GSMenu();

	void Init();
	void Enter();
	void Pause();
	void Resume();
	void Exit();

	void Key(unsigned char key, bool bIsPressed);
	void TouchActionDown(int x, int y);
	void TouchActionMove(int x, int y);
	void TouchActionUp(int x, int y);

	void Update(float dt);
	void Draw();
};

