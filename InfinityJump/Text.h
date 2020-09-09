#pragma once
#include <string>
#include "../3DEngine/3DEngine.h"

class Text 
{
    std::string m_strText;
    Vector2 m_position;
    Vector2 m_scale;
    Vector4 m_color;

public:
    Text();
    Text(const std::string text, Vector4 color, Vector2 position, Vector2 scale);
    ~Text();

    void setText(std::string text);
    void setPosition(Vector2 position);
    void setScale(Vector2 scale);
    void setColor(Vector4 color);

    std::string getText();
    Vector2 getPostion();
    Vector2 getScale();
    Vector4 getColor();

    void Draw();
};

