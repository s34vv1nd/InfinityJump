#pragma once
#include <string>
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
	std::string m_strName;

public:
	Object();
	virtual ~Object();

	void setModel(Model* model);
	void setTextures(std::vector<Texture*> textures);
	void setBlendMap(Texture* blendMap);
	void setDispTexture(Texture* dispTexture);
	void setMaskTexture(Texture* maskTexture);
	void setShaders(Shaders* shaders);

	int getID() { return m_iID; }
	void setID(int id) { m_iID = id; }
	std::string getName() { return m_strName; }
	void setName(std::string name) { m_strName = name; }
	Vector3 getPosition() { return m_position; }
	void setPosition(Vector3 position) { m_position = position; }
	Vector3 getRotation() { return m_rotation; }
	void setRotation(Vector3 rotation) { m_rotation = rotation; }
	Vector3 getScale() { return m_scale; }
	void setScale(Vector3 scale) { m_scale = scale; }

	virtual Matrix calculateWVPmatrix();
	
	virtual void Init();

	virtual void Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH, Vector2 origin) {};

	virtual void addTexture(GLint textureID, GLint textureLoc, GLint textureUnit);

	virtual void Draw();
	
	virtual void Update(float dt);
	
	virtual void CleanUp();
};

