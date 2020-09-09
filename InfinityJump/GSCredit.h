#pragma once
#include <memory>
#include "Define.h"
#include "GameStateBase.h"
#include "Button.h"
#include "Text.h"

class GSCredit : public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static shared_ptr<Button> m_backmenuButton;
	static void onCLickBackMenuButton(int x, int y, bool isPressed);


public:
	GSCredit();
	~GSCredit();
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

