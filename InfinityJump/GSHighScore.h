#pragma once
#include "GameStateBase.h"
class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;
class GSHighScore : public GameStateBase
{
public:
	GSHighScore();
	~GSHighScore();
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

