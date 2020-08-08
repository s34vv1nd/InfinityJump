#include "stdafx.h"
#include "Object.h"
#include <string>


Object::Object():
	m_model(NULL),
	m_heightMap(NULL),
	m_textures(vector<Texture*>(0)), 
	m_blendMap(NULL),
	m_dispTexture(NULL),
	m_maskTexture(NULL),
	m_shaders(0),
	m_position(Vector3(0.0f, 0.0f, 0.0f)),
	m_rotation(Vector3(0.0f, 0.0f, 0.0f)),
	m_scale(Vector3(1.0f, 1.0f, 1.0f)),
	m_fTime(0)
{
	m_worldMtr.SetIdentity();
	m_WVPmtr.SetIdentity();
}

//Object::Object(int id, 
//	Model * model, 
//	vector<Texture*> textures, 
//	HeightMap * heightmap, 
//	Texture * dispTexture,
//	Texture * maskTexture,
//	Shaders * shaders,
//	Vector3 position, 
//	Vector3 rotation, 
//	Vector3 scale
//):
//	m_iID(id), 
//	m_model(model), 
//	m_textures(textures), 
//	m_heightMap(heightmap), 
//	m_dispTexture(dispTexture),
//	m_maskTexture(maskTexture),
//	m_shaders(shaders),
//	m_position(position), 
//	m_rotation(rotation), 
//	m_scale(scale),
//	m_fTime(0)
//{
//	m_worldMtr.SetIdentity();
//	m_model->loadModel(heightmap);
//}

Object::~Object()
{
}

Matrix Object::calculateWVPmatrix()
{
	Camera* camera = Singleton<SceneManager>::GetInstance()->getCamera();
	if (m_textures[0]->getType() == TEXTURE_2D) {
		m_WVPmtr = m_worldMtr * camera->getViewMatrix() * camera->getProjectionMatrix();
	}
	else {
		Matrix V = camera->getViewMatrix();
		for (int i = 0; i < 3; ++i) V.m[i][3] = V.m[3][i] = 0;
		m_WVPmtr = m_worldMtr * V * camera->getProjectionMatrix();
	}
	return m_WVPmtr;
}

int Object::loadFromFile(FILE* fi)
{
	fscanf(fi, "ID %d\n", &m_iID);

	int modelID;
	fscanf(fi, "MODEL %d\n", &modelID);
	m_model = Singleton<ResourceManager>::GetInstance()->getModelByID(modelID);

	int nTextures;
	fscanf(fi, "TEXTURES %d\n", &nTextures);
	if (nTextures) {
		for (int i = 0; i < nTextures; ++i) {
			int id;
			fscanf(fi, "TEXTURE %d\n", &id);
			m_textures.push_back(Singleton<ResourceManager>::GetInstance()->getTextureByID(id));
		}
	}

	int nBlendMaps;
	fscanf(fi, "BLENDMAPS %d\n", &nBlendMaps);
	if (nBlendMaps) {
		int id;
		fscanf(fi, "BLENDMAP %d\n", &id);
		m_blendMap = Singleton<ResourceManager>::GetInstance()->getTextureByID(id);
	}

	int nHeightMaps;
	fscanf(fi, "HEIGHTMAPS %d\n", &nHeightMaps);
	if (nHeightMaps) {
		int id;
		fscanf(fi, "HEIGHTMAP %d\n", &id);
		m_heightMap = Singleton<ResourceManager>::GetInstance()->getHeightMapByID(id);
	}

	int nCubeTextures;
	fscanf(fi, "CUBETEXTURES %d\n", &nCubeTextures);
	if (nCubeTextures) {
		for (int i = 0; i < nCubeTextures; ++i) {
			int id;
			fscanf(fi, "CUBETEXTURE %d\n", &id);
			m_textures.push_back(Singleton<ResourceManager>::GetInstance()->getCubeTextureByID(id));
		}
	}

	int nDispTextures;
	fscanf(fi, "DISPTEXTURES %d\n", &nDispTextures);
	if (nDispTextures) {
		int id;
		fscanf(fi, "DISPTEXTURE %d\n", &id);
		m_dispTexture = Singleton<ResourceManager>::GetInstance()->getTextureByID(id);
	}

	int nMaskTextures;
	fscanf(fi, "MASKTEXTURES %d\n", &nMaskTextures);
	if (nMaskTextures) {
		int id;
		fscanf(fi, "MASKTEXTURE %d\n", &id);
		m_maskTexture = Singleton<ResourceManager>::GetInstance()->getTextureByID(id);
	}

	int shadersID;
	fscanf(fi, "SHADER %d\n", &shadersID);
	m_shaders = Singleton<ResourceManager>::GetInstance()->getShadersByID(shadersID);

	fscanf(fi, "POSITION %f, %f, %f\n", &m_position.x, &m_position.y, &m_position.z);
	fscanf(fi, "ROTATION %f, %f, %f\n", &m_rotation.x, &m_rotation.y, &m_rotation.z);
	m_rotation = m_rotation / 180.0f * PI;
	fscanf(fi, "SCALE %f, %f, %f\n", &m_scale.x, &m_scale.y, &m_scale.z);

	m_worldMtr.SetIdentity();
	m_model->loadModel(m_heightMap);
	return 0;
}

int Object::Init()
{
	Matrix scaleMtr, rotMtrX, rotMtrY, rotMtrZ, translationMtr;
	scaleMtr.SetScale(m_scale);
	rotMtrX.SetRotationX(m_rotation.x);
	rotMtrY.SetRotationY(m_rotation.y);
	rotMtrZ.SetRotationZ(m_rotation.z);
	translationMtr.SetTranslation(m_position);
	m_worldMtr = scaleMtr * rotMtrZ * rotMtrX * rotMtrY * translationMtr;
	return 0;
}

void Object::addTexture(GLint textureID, GLint textureLoc, GLint textureUnit)
{
	glUniform1i(textureLoc, textureUnit);
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

int Object::Draw()
{
	glUseProgram(m_shaders->m_iProgram);
	
	glBindBuffer(GL_ARRAY_BUFFER, *m_model->getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_model->getIBO());

	int nTextures = 0;

	if (m_textures[0]->getType() == TEXTURE_2D) {
		for (int i = 0; i < (int) m_textures.size(); ++i) {
			if (m_shaders->m_textureUniforms[nTextures] != -1) {
				addTexture(*m_textures[i]->getTextureID(), m_shaders->m_textureUniforms[nTextures], nTextures);
				++nTextures;
			}
		}
		if (m_shaders->m_iTextureUniform != -1) {
			addTexture(*m_textures[0]->getTextureID(), m_shaders->m_iTextureUniform, nTextures);
			++nTextures;
		}
	}
	else if (m_textures[0]->getType() == TEXTURE_CUBE) {
		glDepthMask(GL_FALSE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, *m_textures[0]->getTextureID());
		if (m_shaders->m_iCubeUniform != -1) {
			glUniform1i(m_shaders->m_iCubeUniform, 0);
		}
	}

	if (m_shaders->m_iBlendMapUniform != -1) {
		addTexture(*m_blendMap->getTextureID(), m_shaders->m_iBlendMapUniform, nTextures);
		++nTextures;
	}

	if (m_shaders->m_iDispTextureUniform != -1) {
		addTexture(*m_dispTexture->getTextureID(), m_shaders->m_iDispTextureUniform, nTextures);
		++nTextures;
	}

	if (m_shaders->m_iMaskTextureUniform != -1) {
		addTexture(*m_maskTexture->getTextureID(), m_shaders->m_iMaskTextureUniform, nTextures);
		++nTextures;
	}

	if (m_shaders->m_iDispMax != -1) {
		glUniform2f(m_shaders->m_iDispMax, 1.0f, 1.0f);
	}

	if (m_shaders->m_iTimeUniform != -1) {
		glUniform1f(m_shaders->m_iTimeUniform, m_fTime);
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

	if (m_shaders->m_iWVmatrixUniform != -1) {
		Matrix WV = m_worldMtr * Singleton<SceneManager>::GetInstance()->getCamera()->getViewMatrix();
		glUniformMatrix4fv(m_shaders->m_iWVmatrixUniform, 1, GL_FALSE, WV.m[0]);
	}

	if (m_shaders->m_iFogColor != -1) {
		glUniform4f(
			m_shaders->m_iFogColor, 
			Singleton<SceneManager>::GetInstance()->getFogColor().x,
			Singleton<SceneManager>::GetInstance()->getFogColor().y,
			Singleton<SceneManager>::GetInstance()->getFogColor().z,
			Singleton<SceneManager>::GetInstance()->getFogColor().w);
	}

	if (m_shaders->m_iFogMinDist != -1) {
		glUniform1f(m_shaders->m_iFogMinDist, Singleton<SceneManager>::GetInstance()->getFogMinDist());
	}

	if (m_shaders->m_iFogMaxDist != -1) {
		glUniform1f(m_shaders->m_iFogMaxDist, Singleton<SceneManager>::GetInstance()->getFogMaxDist());
	}

	glActiveTexture(GL_TEXTURE0);

	glDrawElements(GL_TRIANGLES, m_model->getNIndices(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	if (m_textures[0]->getType() == TEXTURE_2D) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glDepthMask(GL_TRUE);
	}
	return 0;
}

void Object::Update(float dt)
{
	m_fTime += dt;
}

void Object::CleanUp()
{
	
}
