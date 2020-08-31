#pragma once
#include <string>
#include <memory>
#include "../Utilities/utilities.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "SceneManager.h"
#include "HeightMap.h"

using namespace std;

class Object
{
protected:
	int m_iID;
	shared_ptr<Model> m_model;
	shared_ptr<HeightMap> m_heightMap;
	std::vector<std::shared_ptr<Texture>> m_textures;
	shared_ptr<Texture> m_blendMap;
	shared_ptr<Texture> m_dispTexture;
	shared_ptr<Texture> m_maskTexture;
	shared_ptr<Shaders> m_shaders;
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	Matrix m_worldMtr;
	Matrix m_WVPmtr;
	GLfloat m_fTime;
	std::string m_strName;
	bool m_worldMtrIsChanged;

public:
	Object();
	virtual ~Object();

	shared_ptr<Model> getModel() { return m_model; }
	void setModel(shared_ptr<Model> model);

	std::vector<shared_ptr<Texture>>& getTextures() { return m_textures; }
	void setTextures(std::vector<shared_ptr<Texture>> textures);
	
	void setBlendMap(shared_ptr<Texture> blendMap);
	void setDispTexture(shared_ptr<Texture> dispTexture);
	void setMaskTexture(shared_ptr<Texture> maskTexture);
	
	shared_ptr<Shaders> getShaders() { return m_shaders; }
	void setShaders(shared_ptr<Shaders> shaders);

	int getID() { return m_iID; }
	void setID(int id) { m_iID = id; }
	
	std::string getName() { return m_strName; }
	void setName(std::string name) { m_strName = name; }
	
	Vector3 getPosition() { return m_position; }
	void setPosition(Vector3 position);
	
	Vector3 getRotation() { return m_rotation; }
	void setRotation(Vector3 rotation);

	Vector3 getScale() { return m_scale; }
	void setScale(Vector3 scale);

	virtual Matrix calculateWorldMatrix();

	virtual Matrix calculateWVPmatrix();
	
	virtual void Init();

	//virtual void Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin) {};

	virtual void addTexture(GLint textureID, GLint textureLoc, GLint textureUnit);

	virtual void Draw();
	
	virtual void Update(float dt);
	
	virtual void CleanUp();
};

