#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(int id) : Object(id) {

}

Sprite::~Sprite()
{
}

int Sprite::loadFromFile(FILE* fi)
{
	GLint spriteX, spriteY, spriteW, spriteH, textureW, textureH;
	fscanf(fi, "COORD %d %d %d %d %d %d\n", &spriteX, &spriteY, &spriteW, &spriteH, &textureW, &textureH);

	int textureID;
	fscanf(fi, "TEXTURE %d\n", &textureID);
	m_textures.push_back(Singleton<ResourceManager>::GetInstance()->getTextureByID(textureID));
	
	int shaderID;
	fscanf(fi, "SHADER %d\n", &shaderID);
	m_shaders = Singleton<ResourceManager>::GetInstance()->getShadersByID(shaderID);

	fscanf(fi, "POSITION %f %f %f\n", &m_position.x, &m_position.y, &m_position.z);
	fscanf(fi, "ROTATION %f %f %f\n", &m_rotation.x, &m_rotation.y, &m_rotation.z);
	m_rotation = m_rotation / 180.0f * PI;
	fscanf(fi, "SCALE %f %f %f\n", &m_scale.x, &m_scale.y, &m_scale.z);
	Init(spriteX, spriteY, spriteW, spriteH, textureW, textureH, Vector2(m_position.x, m_position.y));
	return 0;
}

void Sprite::Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin)
{
	m_pos2D = origin;
	m_iWidth = spriteW;
	m_iHeight = spriteH;

	Vertex* verticesData = new Vertex[4];
	Vector3 delta = Vector3(origin.x - (float)spriteW / 2, origin.y - (float)spriteH / 2, 0.0);
	verticesData[0].pos = Vector3(-(float)spriteW / 2, -(float)spriteH / 2, 0.0f) - delta;
	verticesData[1].pos = Vector3((float)spriteW / 2, -(float)spriteH / 2, 0.0f) - delta;
	verticesData[2].pos = Vector3(-(float)spriteW / 2, (float)spriteH / 2, 0.0f) - delta;
	verticesData[3].pos = Vector3((float)spriteW / 2, (float)spriteH / 2, 0.0f) - delta;
	verticesData[0].uv = Vector2((float)spriteX / textureW, (float)(spriteY + spriteH) / textureH);
	verticesData[1].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(spriteY + spriteH) / textureH);
	verticesData[2].uv = Vector2((float)spriteX / textureW, (float)spriteY / textureH);
	verticesData[3].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)spriteY / textureH);

	GLuint indicesData[6] = {0, 1, 2, 1, 2, 3};
	m_model = new Model();
	m_model->Init(4, verticesData, 6, indicesData);
}

void Sprite::setPos2D(GLfloat x, GLfloat y)
{
	m_pos2D.x = x;
	m_pos2D.y = y;
}

Vector2 Sprite::getPos2D()
{
	return m_pos2D;
}

void Sprite::setSize(GLint width, GLint height)
{
	m_iWidth = width;
	m_iHeight = height;
}

GLint Sprite::getWidth()
{
	return m_iWidth;
}

GLint Sprite::getHeight()
{
	return m_iHeight;
}
