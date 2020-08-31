#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

shared_ptr<Model> ResourceManager::getModelByID(int id)
{
	for (auto p : m_modelList)
	if (p) {
		if (p->getID() == id) return p;
	}
	return nullptr;
}

shared_ptr<Texture> ResourceManager::getTextureByID(int id)
{
	for (auto p : m_textureList)
	if (p && p->getType() == TEXTURE_2D) {
		if (p->getID() == id) return p;
	}
	return nullptr;
}

shared_ptr<Texture> ResourceManager::getCubeTextureByID(int id)
{
	for (auto p : m_cubeTextureList)
		if (p && p->getType() == TEXTURE_CUBE) {
			if (p->getID() == id) return p;
		}
	return nullptr;
}

shared_ptr<HeightMap> ResourceManager::getHeightMapByID(int id)
{
	for (auto p : m_heightmapList)
		if (p) {
			if (p->getID() == id) return p;
		}
	return nullptr;
}

shared_ptr<Shaders> ResourceManager::getShadersByID(int id)
{
	for (auto p : m_shadersList)
	if (p) {
		if (p->getID() == id) return p;
	}
	return nullptr;
}

void ResourceManager::CleanUp()
{
	m_modelList.clear();
	m_textureList.clear();
	m_cubeTextureList.clear();
	m_heightmapList.clear();
	m_shadersList.clear();
}

int ResourceManager::Init(const char * srcFile)
{
	FILE *fi = fopen(srcFile, "r");
	if (!fi) {
		printf("FAILED TO OPEN FILE %s\n", srcFile);
		return 1;
	}

	fscanf(fi, "#Models: %d\n", &m_iNModels);
	m_modelList.resize(m_iNModels, NULL);
	for (int i = 0; i < m_iNModels; ++i) {
		int id;
		char modelSrcFile[64];
		fscanf(fi, "ID %d\n", &id);
		fscanf(fi, "FILE %s\n", modelSrcFile);
		m_modelList[i] = make_shared<Model>(id, modelSrcFile);
	}
	fscanf(fi, "\n");

	fscanf(fi, "#2D Textures: %d\n", &m_iNTextures);
	m_textureList.resize(m_iNTextures, NULL);
	for (int i = 0; i < m_iNTextures; ++i) {
		int id;
		char textureSrcFile[100];
		char tiling[20];
		fscanf(fi, "ID %d\n", &id);
		fscanf(fi, "FILE %s\n", textureSrcFile);
		fscanf(fi, "TILING %s\n", tiling);
		m_textureList[i] = make_shared<Texture>(id, strcmp(tiling, "CLAMP") == 0 ? CLAMP_TO_EDGE : REPEAT, TEXTURE_2D);
		m_textureList[i]->loadTexture(textureSrcFile);
	}
	fscanf(fi, "\n");

	fscanf(fi, "#Height Map: %d\n", &m_iNHeightMaps);
	m_heightmapList.resize(m_iNHeightMaps, NULL);
	for (int i = 0; i < m_iNHeightMaps; ++i) {
		int id;
		char heightmapSrcFile[64];
		fscanf(fi, "ID %d\n", &id);
		fscanf(fi, "FILE %s\n", heightmapSrcFile);
		m_heightmapList[i] = make_shared<HeightMap>(id);
		m_heightmapList[i]->loadHeightMap(heightmapSrcFile);
	}
	fscanf(fi, "\n");

	fscanf(fi, "#Cube Textures: %d\n", &m_iNCubeTextures);
	m_cubeTextureList.resize(m_iNCubeTextures, NULL);
	for (int i = 0; i < m_iNCubeTextures; ++i) {
		int id;
		vector<const char*> srcFiles;
		char tiling[20];
		fscanf(fi, "ID %d\n", &id);
		for (int i = 0; i < 6; ++i) {
			char cubeSrcFile[64];
			fscanf(fi, "FILE %s\n", cubeSrcFile);
			srcFiles.push_back(cubeSrcFile);
		}
		fscanf(fi, "TILING %s\n", tiling);
		m_cubeTextureList[i] = make_shared<Texture>(id, strcmp(tiling, "REPEAT") == 0 ? REPEAT : CLAMP_TO_EDGE, TEXTURE_CUBE);
		m_cubeTextureList[i]->loadCubeTexture(srcFiles);
	}
	fscanf(fi, "\n");

	fscanf(fi, "#Shaders: %d\n", &m_iNShaders);
	m_shadersList.resize(m_iNShaders, NULL);
	for (int i = 0; i < m_iNShaders; ++i) {
		int id;
		char vsFile[64], fsFile[64];
		fscanf(fi, "ID %d\n", &id);
		fscanf(fi, "VS %s\n", vsFile);
		fscanf(fi, "FS %s\n", fsFile);
		m_shadersList[i] = make_shared<Shaders>(id);
		if (m_shadersList[i]->Init(vsFile, fsFile) != 0) {
			printf("FAILED TO LOAD SHADERS %d\n", i);
			return 2;
		}
	}

	fclose(fi);
	return 0;
}
