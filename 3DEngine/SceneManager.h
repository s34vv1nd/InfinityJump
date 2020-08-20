#pragma once
#include <vector>
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
	vector<Object*> m_objList;
	GLint m_iNObjects = 0;
	Camera* m_camera = 0;
	GLuint m_pressedBtns = 0;
	Vector4 m_fogColor;
	GLfloat m_fogMinDist = 0, m_fogMaxDist = 0;

	Sprite* loadSpriteFromFile(FILE* fi);
	AnimSprite* loadAnimSpriteFromFile(FILE* fi);
	Object* loadObjectFromFile(FILE* fi);
public:
	SceneManager();
	~SceneManager();

	Camera* getCamera() { return m_camera; }
	Vector4 getFogColor() { return m_fogColor; }
	GLfloat getFogMinDist() { return m_fogMinDist; }
	GLfloat getFogMaxDist() { return m_fogMaxDist; }
	
	int Init(const char* srcFile);
	void Draw();
	void Update(float deltaTime);
	void Key(unsigned char key, bool bIsPressed);
	void CleanUp();
};

