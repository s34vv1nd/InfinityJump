#include "stdafx.h"
#include "Text.h"

Text::Text()
{
}

Text::Text(const std::string text, Vector4 color, Vector2 position, Vector2 scale):
	m_strText(text),
	m_color(color),
	m_position(position),
	m_scale(scale)
{
}

Text::~Text()
{
}

void Text::setText(std::string text)
{
	m_strText = text;
}

void Text::setPosition(Vector2 position)
{
	m_position = position;
}

void Text::setScale(Vector2 scale)
{
	m_scale = scale;
}

void Text::setColor(Vector4 color)
{
	m_color = color;
}

std::string Text::getText()
{
	return m_strText;
}

Vector2 Text::getPostion()
{
	return m_position;
}

Vector2 Text::getScale()
{
	return m_scale;
}

Vector4 Text::getColor()
{
	return m_color;
}

void Text::Draw()
{
	Singleton<TextManager>::GetInstance()->Render(m_strText.c_str(), m_color, m_position.x, m_position.y, m_scale.x, m_scale.y);
}
