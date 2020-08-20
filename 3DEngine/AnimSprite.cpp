#include "stdafx.h"
#include "AnimSprite.h"

AnimSprite::AnimSprite() :
	Sprite()
{
}

AnimSprite::~AnimSprite()
{
}

void AnimSprite::setAnimations(vector<Animation*> animations, int animationID)
{
	m_animations = animations;
	m_currentAnimation = getAnimation(animationID);
}

void AnimSprite::pushAnimation(Animation* animation)
{
	m_animations.push_back(animation);
}

void AnimSprite::setCurrentAnimation(int animationID)
{
	m_currentAnimation = getAnimation(animationID);
}

Animation* AnimSprite::getAnimation(int animationID)
{
	for (auto anim : m_animations) {
		if (anim->getID() == animationID) {
			return anim;
		}
	}
	return NULL;
}

int AnimSprite::getCountAnimations()
{
	return m_animations.size();
}

void AnimSprite::Draw()
{
	glUseProgram(m_shaders->m_iProgram);

	glBindBuffer(GL_ARRAY_BUFFER, *m_model->getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_model->getIBO());

	if (m_shaders->m_iTextureUniform != -1) {
		Texture* texture = m_currentAnimation->getFrame(m_currentAnimation->getCurrentFrame());
		addTexture(*texture->getTextureID(), m_shaders->m_iTextureUniform, 0);
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

void AnimSprite::Update(GLfloat dt)
{
	// m_fTime += dt;
	m_currentAnimation->Update(dt);
}
