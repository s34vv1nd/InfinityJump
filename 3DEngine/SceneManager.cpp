#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager():
	m_camera(0)
{
}


SceneManager::~SceneManager()
{
}

int SceneManager::Init(const char* srcFile)
{
	FILE *fi = fopen(srcFile, "r");
	if (!fi) {
		printf("FAILED TO OPEN FILE \"%s\"\n", srcFile);
		return 1;
	}

	fscanf(fi, "#Objects: %d\n", &m_iNObjects);
	m_objList.resize(m_iNObjects, NULL);
	for (int i = 0; i < m_iNObjects; ++i) {
		int id;
		fscanf(fi, "ID %d\n", &id);
		m_objList[i] = new Object();
		m_objList[i]->loadFromFile(fi);
		if (m_objList[i]->Init() != 0) {
			printf("FAILED TO LOAD OBJECT %d\n", i);
			return 2;
		}
	}
	fscanf(fi, "\n");

	fscanf(fi, "#CAMERA\n");
	GLfloat _near, _far, _fov, _speed, _rotspeed;
	fscanf(fi, "NEAR %f\n", &_near);
	fscanf(fi, "FAR %f\n", &_far);
	fscanf(fi, "FOV %f\n", &_fov);
	fscanf(fi, "SPEED %f\n", &_speed);
	fscanf(fi, "ROTATIONSPEED %f\n", &_rotspeed);
	Matrix P;
	GLfloat _aspect = Globals::screenWidth * 1.0f / Globals::screenHeight;
	m_camera = new Camera(_speed, _rotspeed, P.SetPerspective(_fov, _aspect, _near, _far));

	fscanf(fi, "#FOG\n");
	fscanf(fi, "COLOR %f, %f, %f, %f\n", &m_fogColor.x, &m_fogColor.y, &m_fogColor.z, &m_fogColor.w);
	fscanf(fi, "MINDIST %f\n", &m_fogMinDist);
	fscanf(fi, "MAXDIST %f\n", &m_fogMaxDist);

	for (Object* obj : m_objList) 
		if (obj) {
			obj->calculateWVPmatrix();
		}

	return 0;
}

void SceneManager::Draw()
{
	for (int i = 0; i < m_iNObjects; ++i)
		if (m_objList[i]) {
			m_objList[i]->Draw();
		}
}

void SceneManager::Update(float dt)
{
	m_camera->update(dt, m_pressedBtns);
	for (int i = 0; i < m_iNObjects; ++i)
		if (m_objList[i]) {
			if (m_pressedBtns) m_objList[i]->calculateWVPmatrix();
			m_objList[i]->Update(dt);
		}
}

void SceneManager::Key(unsigned char key, bool bIsPressed)
{
	//printf("Pressed: %d %d\n", key, bIsPressed);
	switch (key) {
	case VK_UP:	//MOVE UP
		if (bIsPressed) 
			m_pressedBtns |= BIT_MOVE_FORWARD;
		else
			m_pressedBtns &= ~BIT_MOVE_FORWARD;
		break;
	
	case VK_DOWN:	//MOVE DOWN
		if (bIsPressed) 
			m_pressedBtns |= BIT_MOVE_BACKWARD; 
		else 
			m_pressedBtns ^= BIT_MOVE_BACKWARD;
		break;

	case VK_LEFT:	//MOVE LEFT
		if (bIsPressed) 
			m_pressedBtns |= BIT_MOVE_LEFT; 
		else 
			m_pressedBtns ^= BIT_MOVE_LEFT;
		break;

	case VK_RIGHT:	//MOVE RIGHT
		if (bIsPressed) 
			m_pressedBtns |= BIT_MOVE_RIGHT; 
		else 
			m_pressedBtns ^= BIT_MOVE_RIGHT;
		break;

	case 'w':
	case 'W':	// W : ROTATE UP
		if (bIsPressed) 
			m_pressedBtns |= BIT_ROTATE_UP; 
		else 
			m_pressedBtns ^= BIT_ROTATE_UP;
		break;

	case 's':
	case 'S':	// S : ROTATE DOWN
		if (bIsPressed) 
			m_pressedBtns |= BIT_ROTATE_DOWN; 
		else 
			m_pressedBtns ^= BIT_ROTATE_DOWN;
		break;

	case 'a':
	case 'A':	// A : ROTATE LEFT
		if (bIsPressed) 
			m_pressedBtns |= BIT_ROTATE_LEFT; 
		else 
			m_pressedBtns ^= BIT_ROTATE_LEFT;
		break;

	case 'd':
	case 'D':	// D : ROTATE RIGHT
		if (bIsPressed) 
			m_pressedBtns |= BIT_ROTATE_RIGHT; 
		else 
			m_pressedBtns ^= BIT_ROTATE_RIGHT;
		break;
	}
}

void SceneManager::CleanUp()
{
	for (int i = 0; i < m_iNObjects; ++i) {
		m_objList[i]->CleanUp();
		SAFE_DEL(m_objList[i]);
	}
}
