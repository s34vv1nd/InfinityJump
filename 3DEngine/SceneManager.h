#pragma once
#include <vector>
#include <memory>
#include "../Utilities/utilities.h"
#include "Math.h"
#include "Object.h"
#include "Singleton.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Globals.h"


using namespace std;

class Object;
class Sprite;
class AnimSprite;

class SceneManager
{
	GLint m_iNObjects = 0;
	shared_ptr<Camera> m_camera = 0;
	GLuint m_pressedBtns = 0;
	Vector4 m_fogColor;
	GLfloat m_fogMinDist = 0, m_fogMaxDist = 0;

	shared_ptr<Sprite> loadSpriteFromFile(FILE* fi);
	shared_ptr<AnimSprite> loadAnimSpriteFromFile(FILE* fi);
	shared_ptr<Object> loadObjectFromFile(FILE* fi);
public:
	SceneManager();
	~SceneManager();

	shared_ptr<Camera> getCamera() { return m_camera; }
	Vector4 getFogColor() { return m_fogColor; }
	GLfloat getFogMinDist() { return m_fogMinDist; }
	GLfloat getFogMaxDist() { return m_fogMaxDist; }

	shared_ptr<Object> getObjectByID(int id);
	shared_ptr<Object> getObjectByName(const string name);
	
	int Init(const char* srcFile);
	void Draw();
	void Update(float deltaTime);
	void Key(unsigned char key, bool bIsPressed);
	void CleanUp();

	std::vector<std::shared_ptr<Object>> m_objList;
};

