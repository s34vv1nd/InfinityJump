#pragma once
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "GameStateBase.h"
#include "Button.h"

class GSPause : 
	public GameStateBase
{
	static shared_ptr<Sprite> m_crown;
	static shared_ptr<Sprite> m_pause;
	static shared_ptr<Button> m_restartButton;
	static shared_ptr<Button> m_resumeButton;
	static shared_ptr<Button> m_exitButton;

	static void OnClickExitButton(int x, int y, bool isPressed, void* context);
	static void OnClickRestartButton(int x, int y, bool isPressed, void* context);
	static void OnClickResumeButton(int x, int y, bool isPressed, void* context);
public:
	GSPause();
	~GSPause();
	
	virtual void Init();
	virtual void Enter() {}
	virtual void Exit() {}
	virtual void Pause() {}
	virtual void Resume() {}

	virtual void Key(unsigned char key, bool bIsPressed) {}
	virtual void TouchActionDown(int x, int y) {}
	virtual void TouchActionMove(int x, int y) {}
	virtual void TouchActionUp(int x, int y);

	virtual void Update(float dt) {}
	virtual void Draw();
};

