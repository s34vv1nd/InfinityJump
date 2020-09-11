#pragma once
#include "Object.h"

class Object;

class Sprite :
    public Object
{
protected:
    GLfloat m_fWidth, m_fHeight;
	Vector2 m_hitbox;
    //std::string m_strText;

public:
    Sprite();
    virtual ~Sprite();
    virtual void Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin);
    virtual void Draw();
    virtual void Update(GLfloat dt);

    virtual void setPos2D(Vector2 pos2D);
	virtual Vector2 getPos2D();
    virtual void setSize(GLfloat width, GLfloat height);
	virtual GLfloat getWidth();
	virtual GLfloat getHeight();
	virtual Vector2 getHitbox();
	//void setText(const std::string text);
	//std::string getText();
};

