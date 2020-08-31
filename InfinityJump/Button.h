#pragma once
#include "../3DEngine/Sprite.h"

class Button : public Sprite
{
	bool m_isClicked = false;
	void (*m_onClickCallback)(int x, int y, bool isPressed);

public:
	Button(shared_ptr<Sprite> obj, void (*onClick)(int x, int y, bool isPressed));
	~Button();

	bool mouseInsideButton(int x, int y);
	bool onClick(int x, int y, bool isPressed);
};

