#pragma once
#include "Object.h"

class Object;

class Sprite :
    public Object
{
protected:
    Vector2 m_pos2D;
    GLint m_iWidth, m_iHeight;
    // string m_Text;

public:
    Sprite(int id);
    virtual ~Sprite();
    virtual int loadFromFile(FILE* fi);
    virtual void Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin);

    void setPos2D(GLfloat x, GLfloat y);
    Vector2 getPos2D();
    void setSize(GLint width, GLint height);
    GLint getWidth();
    GLint getHeight();
};

