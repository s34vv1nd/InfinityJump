#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "SceneManager.h"
#include "HeightMap.h"

class Object
{
protected:
	int m_iID;
	Model* m_model;
	HeightMap* m_heightMap;
	std::vector<Texture*> m_textures;
	Texture* m_blendMap;
	Texture* m_dispTexture;
	Texture* m_maskTexture;
	Shaders* m_shaders;
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	Matrix m_worldMtr;
	Matrix m_WVPmtr;
	GLfloat m_fTime;

public:
	Object(int id);
	virtual ~Object();

	int getID() { return m_iID; }

	virtual Matrix calculateWVPmatrix();

	virtual int loadFromFile(FILE* fi);
	
	virtual int Init();

	virtual void Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin) {};

	virtual void addTexture(GLint textureID, GLint textureLoc, GLint textureUnit);

	virtual int Draw();
	
	virtual void Update(float dt);
	
	virtual void CleanUp();
};

