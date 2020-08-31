#pragma once
#include <deque>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "Character.h"
#include "Pad.h"
#include "ContactListener.h"
#include "StatesType.h"

class GSPlay : public Game
{
public:
	GSPlay();
	~GSPlay();
	int Init();
	void Exit();
	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
};

