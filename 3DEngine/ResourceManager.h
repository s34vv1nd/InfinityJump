#pragma once
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "HeightMap.h"
#include "Globals.h"

using namespace std;

class ResourceManager
{
	vector<Model*> m_modelList;
	vector<Texture*> m_textureList;
	vector<Texture*> m_cubeTextureList;
	vector<Shaders*> m_shadersList;
	vector<HeightMap*> m_heightmapList;

	int m_iNModels;
	int m_iNTextures;
	int m_iNCubeTextures;
	int m_iNShaders;
	int m_iNHeightMaps;
public:
	ResourceManager();
	~ResourceManager();

	int Init(const char* srcFile);

	Model* getModelByID(int id);
	Texture* getTextureByID(int id);
	Texture* getCubeTextureByID(int id);
	HeightMap* getHeightMapByID(int id);
	Shaders* getShadersByID(int id);

	void CleanUp();
};

