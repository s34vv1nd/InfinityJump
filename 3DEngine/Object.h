#pragma once
#include <vector>
#include "../Utilities/utilities.h"
#include "Math.h"
#include "define.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "SceneManager.h"
#include "HeightMap.h"

class Object
{
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
	Object();
	//Object(int id,
	//	Model* model,
	//	std::vector<Texture*> textures,
	//	HeightMap* heightmap,
	//	Texture * dispTexture,
	//	Texture * maskTexture,
	//	Shaders * shaders, 
	//	Vector3 position, 
	//	Vector3 rotation, 
	//	Vector3 scale
	//);
	virtual ~Object();

	int getID() { return m_iID; }

	Matrix calculateWVPmatrix();

	int loadFromFile(FILE* fi);
	
	int Init();

	void addTexture(GLint textureID, GLint textureLoc, GLint textureUnit);
	int Draw();
	
	void Update(float dt);
	
	void CleanUp();
};

