#pragma once
#include "../3DEngine/3DEngine.h"
#include "StatesType.h"
#include "GSPlay.h"


class Game
{
public:
	Game();
	~Game();
	StatesType m_StateType;
	bool m_Music;

	void Initialize();
	void Draw();
	void SwitchStateByKey(StatesType state, unsigned char key, bool bIsPressed);
};

