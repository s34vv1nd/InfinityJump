#pragma once
#include <memory>
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "HeightMap.h"
#include "Globals.h"

using namespace std;

class ResourceManager
{
	vector<shared_ptr<Model>> m_modelList;
	vector<shared_ptr<Texture>> m_textureList;
	vector<shared_ptr<Texture>> m_cubeTextureList;
	vector<shared_ptr<Shaders>> m_shadersList;
	vector<shared_ptr<HeightMap>> m_heightmapList;

	int m_iNModels;
	int m_iNTextures;
	int m_iNCubeTextures;
	int m_iNShaders;
	int m_iNHeightMaps;
public:
	ResourceManager();
	~ResourceManager();

	int Init(const char* srcFile);

	shared_ptr<Model> getModelByID(int id);
	shared_ptr<Texture> getTextureByID(int id);
	shared_ptr<Texture> getCubeTextureByID(int id);
	shared_ptr<HeightMap> getHeightMapByID(int id);
	shared_ptr<Shaders> getShadersByID(int id);

	void CleanUp();
};

