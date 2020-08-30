#pragma once
#include "Object.h"

class Object;

class Sprite :
    public Object
{
protected:
    GLint m_iWidth, m_iHeight;
    // string m_Text;

public:
    Sprite();
    virtual ~Sprite();
    virtual void Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin);
    virtual void Draw();
    virtual void Update(GLfloat dt);

    virtual void setPos2D(GLfloat x, GLfloat y);
    Vector2 getPos2D();
    virtual void setSize(GLint width, GLint height);
    GLint getWidth();
    GLint getHeight();
};

