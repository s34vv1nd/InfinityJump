#pragma once
#include <memory>
#include "Define.h"
#include "GameStateBase.h"
#include "Button.h"
#include "Text.h"
class GSHelp : public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static shared_ptr<Sprite> m_textBoard;
	static shared_ptr<Button> m_backmenuButton;
	static void onCLickBackMenuButton(int x, int y, bool isPressed, void* context);

public:
	GSHelp();
	~GSHelp();
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

