#pragma once
#include "../3DEngine/Sprite.h"

class Button : public Sprite
{
	bool isClicked;
	void *onClick();
public:
	Button();
	~Button();
};

