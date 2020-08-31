#pragma once
#include <deque>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "Character.h"
#include "Pad.h"
#include "ContactListener.h"
#include "GSPlay.h"
#include "GSMenu.h"

class ContactListener;

class Game
{

public:
	Game();
	~Game();

	void Init();
	void Draw();
	void Update(GLfloat dt);
	void Key(unsigned char key, bool bIsPressed);
	void TouchActionDown(int x, int y);
	void TouchActionUp(int x, int y);
	void TouchActionMove(int x, int y);
	void CleanUp();
};

