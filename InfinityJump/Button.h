#pragma once
#include "../3DEngine/Sprite.h"
#include "SoundManager.h"

class Button : public Sprite
{
	bool m_isClicked = false;
	void (*m_onClickCallback)(int x, int y, bool isPressed, void* context);

public:
	Button(shared_ptr<Sprite> obj, void (*onClick)(int x, int y, bool isPressed, void* context));
	~Button();

	bool mouseInsideButton(int x, int y);
	bool onClick(int x, int y, bool isPressed, void* context = NULL);
};

