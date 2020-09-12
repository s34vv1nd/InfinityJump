#include "stdafx.h"
#include "Button.h"


Button::Button(shared_ptr<Sprite> obj, void(*onClick)(int x, int y, bool isPressed, void* context))
{
	m_model = obj->getModel();
	m_textures = obj->getTextures();
	m_shaders = obj->getShaders();
	m_position = obj->getPosition();
	m_scale = obj->getScale();
	m_rotation = obj->getRotation();
	m_fWidth = obj->getWidth();
	m_fHeight = obj->getHeight();
	calculateWorldMatrix();
	calculateWVPmatrix();
	m_onClickCallback = onClick;
}

Button::~Button()
{
}

bool Button::mouseInsideButton(int x, int y)
{
	return 
		getPos2D().x < x &&
		getPos2D().x + getWidth() > x &&
		getPos2D().y < Globals::screenHeight - y &&
		getPos2D().y + getHeight() > Globals::screenHeight - y;
}

bool Button::onClick(int x, int y, bool isPressed, void* context)
{
	if (m_onClickCallback) {
		
		//printf("Mouse: x = %d , y = %d\n", x, Globals::screenHeight - y);
		//printf("Button: x = %f , y = %f , width = %f , height = %f\n", m_position.x, m_position.y, m_fWidth, m_fHeight);
		if (mouseInsideButton(x, y)) {
			(*m_onClickCallback)(x, y, isPressed, context);
			Singleton<SoundManager>::GetInstance()->playSFX(CLICK_BUTTON);
			return true;
		}
	}
	return false;
}
