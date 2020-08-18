#pragma once
#include "GameStateBase.h"
class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;
class GSWelcom : public GameStateBase
{
public:
	GSWelcom();
	~GSWelcom();
	void Init();
	void Exit();
	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
//private:
};

