#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite() : 
	Object() 
{
}

Sprite::~Sprite()
{
}

void Sprite::Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin)
{
	m_iWidth = spriteW * m_scale.x;
	m_iHeight = spriteH * m_scale.y;

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

	//for (int i = 0; i < 4; ++i) {
	//	printf("x: %f, y: %f, z: %f\n", verticesData[i].pos.x, verticesData[i].pos.y, verticesData[i].pos.z);
	//}

	GLuint indicesData[6] = {0, 1, 2, 1, 2, 3};
	m_model = make_shared<Model>();
	m_model->Init(4, verticesData, 6, indicesData);
}

void Sprite::Draw()
{
	glUseProgram(m_shaders->m_iProgram);

	glBindBuffer(GL_ARRAY_BUFFER, *m_model->getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_model->getIBO());

	if (m_shaders->m_iTextureUniform != -1) {
		addTexture(*m_textures[0]->getTextureID(), m_shaders->m_iTextureUniform, 0);
	}

	if (m_shaders->m_iPositionAttribute != -1)
	{
		glEnableVertexAttribArray(m_shaders->m_iPositionAttribute);
		glVertexAttribPointer(m_shaders->m_iPositionAttribute, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, pos));
	}

	if (m_shaders->m_iTextureAttribute != -1) {
		glEnableVertexAttribArray(m_shaders->m_iTextureAttribute);
		glVertexAttribPointer(m_shaders->m_iTextureAttribute, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, uv));
	}

	if (m_shaders->m_iWVPmatrixUniform != -1) {
		glUniformMatrix4fv(m_shaders->m_iWVPmatrixUniform, 1, GL_FALSE, m_WVPmtr.m[0]);
	}

	glActiveTexture(GL_TEXTURE0);

	glDrawElements(GL_TRIANGLES, m_model->getNIndices(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::Update(GLfloat dt)
{
	Object::Update(dt);
}

void Sprite::setPos2D(GLfloat x, GLfloat y)
{
	setPosition(Vector3(x, y, m_position.z));
}

Vector2 Sprite::getPos2D()
{
	return Vector2(m_position.x, m_position.y);
}

void Sprite::setSize(GLfloat width, GLfloat height)
{
	m_scale.x *= width / m_iWidth;
	m_scale.y *= height / m_iHeight;
	setScale(m_scale);
	m_iWidth = width;
	m_iHeight = height;
}

GLfloat Sprite::getWidth()
{
	return m_iWidth;
}

GLfloat Sprite::getHeight()
{
	return m_iHeight;
}
