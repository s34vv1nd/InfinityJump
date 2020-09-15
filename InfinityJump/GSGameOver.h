#pragma once
#include "Define.h"
#include "GameStateBase.h"
#include "Button.h"
#include "GSPlay.h"

class GSGameOver :
	public GameStateBase
{
	static shared_ptr<Button> m_newGameButton;
	static shared_ptr<Button> m_exitButton;

	static void OnClickRestartButton(int x, int y, bool isPressed, void* context);
	static void OnClickExitButton(int x, int y, bool isPressed, void* context);
public:
	GSGameOver();
	~GSGameOver();

	virtual void Init();
	virtual void Enter();
	virtual void Exit();
	virtual void Pause() {}
	virtual void Resume() {}

	virtual void Key(unsigned char key, bool bIsPressed) {}
	virtual void TouchActionDown(int x, int y) {}
	virtual void TouchActionMove(int x, int y) {}
	virtual void TouchActionUp(int x, int y);

	virtual void Update(float dt);
	virtual void Draw();
};

