#pragma once
#include "GameStateBase.h"
#include "Game.h"
class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;
class GSMenu : public GameStateBase
{

public:
	GSMenu();
	~GSMenu();
	void Init();
	void Exit();
	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
private:
	
};

