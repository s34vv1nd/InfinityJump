#pragma once
#include <memory>
#include "Define.h"
#include "GameStateBase.h"
#include "Button.h"
#include "Text.h"

class GSMenu : public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static shared_ptr<Button> m_playButton;
	static shared_ptr<Button> m_helpButton;
	static shared_ptr<Button> m_creditButton;
	static shared_ptr<Button> m_settingButton;
	static void onClickHelpButton(int x, int y, bool isPressed);
	static void onClickCreditButton(int x, int y, bool isPressed);
	static void onClickPlayButton(int x, int y, bool isPressed);
	static void onClickSettingButton(int x, int y, bool isPressed);
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

