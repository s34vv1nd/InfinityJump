#pragma once
#include "GameStateBase.h"

class GSPlay : public GameStateBase
{
public:
	GSPlay();
	~GSPlay();
	void Init();
	void Exit();
	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
};

