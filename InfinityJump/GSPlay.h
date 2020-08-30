#pragma once
#include "GameStateBase.h"
#include "../3DEngine/Singleton.h"
#include "../Utilities/utilities.h" 
//class Sprite2D;
//class Sprite3D;
//class Text;
//class SpriteAnimation;
class GSPlay //: public GameStateBase
{
public:
	GSPlay();
	~GSPlay();
	void Init();
	void Pause();
	void Resume();
	void Render();
	void Play();
	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
};

