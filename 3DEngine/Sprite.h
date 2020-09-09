#pragma once
#include "Object.h"

class Object;

class Sprite :
    public Object
{
protected:
    GLfloat m_iWidth, m_iHeight;
    //std::string m_strText;

public:
    Sprite();
    virtual ~Sprite();
    virtual void Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin);
    virtual void Draw();
    virtual void Update(GLfloat dt);

    virtual void setPos2D(GLfloat x, GLfloat y);
    Vector2 getPos2D();
    virtual void setSize(GLfloat width, GLfloat height);
    GLfloat getWidth();
    GLfloat getHeight();

	//void setText(const std::string text);
	//std::string getText();
};

