#include "stdafx.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "AnimSprite.h"


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
		char name[64], type[16];
		fscanf(fi, "ID %d\n", &id);
		fscanf(fi, "NAME %s\n", name);
		fscanf(fi, "TYPE %s\n", type);
		if (strcmp(type, "SPRITE") == 0) {
			m_objList[i] = loadSpriteFromFile(fi);
		}
		else if (strcmp(type, "ANIMSPRITE") == 0) {
			m_objList[i] = loadAnimSpriteFromFile(fi);
		}
		else {
			m_objList[i] = loadObjectFromFile(fi);
		}
		m_objList[i]->setID(id);
		m_objList[i]->setName(name);
		m_objList[i]->Init();
	}
	fscanf(fi, "\n");

	fscanf(fi, "#CAMERA\n");
	GLfloat _near, _far, _left, _right, _top, _bottom, _fov, _speed, _rotspeed;
	fscanf(fi, "NEAR %f\n", &_near);
	fscanf(fi, "FAR %f\n", &_far);
	fscanf(fi, "FOV %f\n", &_fov);
	fscanf(fi, "SPEED %f\n", &_speed);
	fscanf(fi, "ROTATIONSPEED %f\n", &_rotspeed);
	m_camera = new Camera(_near, _far, _fov, _speed, _rotspeed);

	fscanf(fi, "#FOG\n");
	fscanf(fi, "COLOR %f, %f, %f, %f\n", &m_fogColor.x, &m_fogColor.y, &m_fogColor.z, &m_fogColor.w);
	fscanf(fi, "MINDIST %f\n", &m_fogMinDist);
	fscanf(fi, "MAXDIST %f\n", &m_fogMaxDist);

	for (Object* obj : m_objList) 
		if (obj) {
			obj->calculateWVPmatrix();
		}
	fclose(fi);
	return 0;
}

Sprite* SceneManager::loadSpriteFromFile(FILE* fi)
{
	Sprite* sprite = new Sprite();
	GLint spriteX, spriteY, spriteW, spriteH, textureW, textureH;
	fscanf(fi, "COORD %d %d %d %d %d %d\n", &spriteX, &spriteY, &spriteW, &spriteH, &textureW, &textureH);

	vector<Texture*> textures;
	int textureID;
	fscanf(fi, "TEXTURE %d\n", &textureID);
	textures.push_back(Singleton<ResourceManager>::GetInstance()->getTextureByID(textureID));
	sprite->setTextures(textures);

	int shaderID;
	fscanf(fi, "SHADER %d\n", &shaderID);
	Shaders* shaders = Singleton<ResourceManager>::GetInstance()->getShadersByID(shaderID);
	sprite->setShaders(shaders);

	Vector3 position, rotation, scale;
	fscanf(fi, "POSITION %f %f %f\n", &position.x, &position.y, &position.z);
	fscanf(fi, "ROTATION %f %f %f\n", &rotation.x, &rotation.y, &rotation.z);
	rotation = rotation / 180.0f * PI;
	fscanf(fi, "SCALE %f %f %f\n", &scale.x, &scale.y, &scale.z);
	sprite->setPosition(position);
	sprite->setRotation(rotation);
	sprite->setScale(scale);
	sprite->Init(spriteX, spriteY, spriteW, spriteH, textureW, textureH, Vector2(0, 0));
	return sprite;
}

AnimSprite* SceneManager::loadAnimSpriteFromFile(FILE* fi)
{
	AnimSprite* animSprite = new AnimSprite();
	GLint spriteX, spriteY, spriteW, spriteH, textureW, textureH;
	fscanf(fi, "COORD %d %d %d %d %d %d\n", &spriteX, &spriteY, &spriteW, &spriteH, &textureW, &textureH);

	char spriteFile[64];
	fscanf(fi, "FILE %s\n", spriteFile);
	FILE* fSprite = fopen(spriteFile, "r");
	if (fSprite == NULL) {
		printf("FAILED TO OPEN FILE %s\n", spriteFile);
		return NULL;
	}
	int nAnims;
	fscanf(fSprite, "#Animations: %d\n", &nAnims);
	vector<Animation*> anims;
	for (int i = 0; i < nAnims; ++i) {
		int id, cntFrames;
		fscanf(fSprite, "ID %d\n", &id);
		fscanf(fSprite, "TEXTURES %d\n", &cntFrames);
		vector<Texture*> frames;
		for (int j = 0; j < cntFrames; ++j) {
			int textureID;
			fscanf(fSprite, "TEXTURE %d\n", &textureID);
			frames.push_back(Singleton<ResourceManager>::GetInstance()->getTextureByID(textureID));
		}
		GLfloat spf;
		fscanf(fSprite, "SPF %f\n", &spf);
		Animation* anim = new Animation(id, frames, 0);
		anim->setSPF(spf);
		anims.push_back(anim);
	}
	animSprite->setAnimations(anims);
	fclose(fSprite);

	int shaderID;
	fscanf(fi, "SHADER %d\n", &shaderID);
	Shaders* shaders = Singleton<ResourceManager>::GetInstance()->getShadersByID(shaderID);
	animSprite->setShaders(shaders);

	Vector3 position, rotation, scale;
	fscanf(fi, "POSITION %f %f %f\n", &position.x, &position.y, &position.z);
	fscanf(fi, "ROTATION %f %f %f\n", &rotation.x, &rotation.y, &rotation.z);
	rotation = rotation / 180.0f * PI;
	fscanf(fi, "SCALE %f %f %f\n", &scale.x, &scale.y, &scale.z);
	animSprite->setPosition(position);
	animSprite->setRotation(rotation);
	animSprite->setScale(scale);
	animSprite->Init(spriteX, spriteY, spriteW, spriteH, textureW, textureH, Vector2(position.x, position.y));
	return animSprite;
}

Object* SceneManager::loadObjectFromFile(FILE* fi)
{
	Object* object = new Object();

	int modelID;
	fscanf(fi, "MODEL %d\n", &modelID);
	Model* model = Singleton<ResourceManager>::GetInstance()->getModelByID(modelID);
	object->setModel(model);

	int nTextures;
	fscanf(fi, "TEXTURES %d\n", &nTextures);
	if (nTextures) {
		vector<Texture*> textures;
		for (int i = 0; i < nTextures; ++i) {
			int id;
			fscanf(fi, "TEXTURE %d\n", &id);
			textures.push_back(Singleton<ResourceManager>::GetInstance()->getTextureByID(id));
		}
		object->setTextures(textures);
	}
	

	int nBlendMaps;
	fscanf(fi, "BLENDMAPS %d\n", &nBlendMaps);
	if (nBlendMaps) {
		int id;
		fscanf(fi, "BLENDMAP %d\n", &id);
		Texture* blendMap = Singleton<ResourceManager>::GetInstance()->getTextureByID(id);
		object->setBlendMap(blendMap);
	}

	int nHeightMaps;
	fscanf(fi, "HEIGHTMAPS %d\n", &nHeightMaps);
	HeightMap* heightMap = NULL;
	if (nHeightMaps) {
		int id;
		fscanf(fi, "HEIGHTMAP %d\n", &id);
		heightMap = Singleton<ResourceManager>::GetInstance()->getHeightMapByID(id);
	}

	int nCubeTextures;
	fscanf(fi, "CUBETEXTURES %d\n", &nCubeTextures);
	if (nCubeTextures) {
		vector<Texture*> textures;
		for (int i = 0; i < nCubeTextures; ++i) {
			int id;
			fscanf(fi, "CUBETEXTURE %d\n", &id);
			textures.push_back(Singleton<ResourceManager>::GetInstance()->getCubeTextureByID(id));
		}
		object->setTextures(textures);
	}

	int nDispTextures;
	fscanf(fi, "DISPTEXTURES %d\n", &nDispTextures);
	if (nDispTextures) {
		int id;
		fscanf(fi, "DISPTEXTURE %d\n", &id);
		Texture* dispTexture = Singleton<ResourceManager>::GetInstance()->getTextureByID(id);
		object->setDispTexture(dispTexture);
	}

	int nMaskTextures;
	fscanf(fi, "MASKTEXTURES %d\n", &nMaskTextures);
	if (nMaskTextures) {
		int id;
		fscanf(fi, "MASKTEXTURE %d\n", &id);
		Texture* maskTexture = Singleton<ResourceManager>::GetInstance()->getTextureByID(id);
		object->setMaskTexture(maskTexture);
	}

	int shaderID;
	fscanf(fi, "SHADER %d\n", &shaderID);
	Shaders* shaders = Singleton<ResourceManager>::GetInstance()->getShadersByID(shaderID);
	object->setShaders(shaders);

	Vector3 position, rotation, scale;
	fscanf(fi, "POSITION %f %f %f\n", &position.x, &position.y, &position.z);
	fscanf(fi, "ROTATION %f %f %f\n", &rotation.x, &rotation.y, &rotation.z);
	rotation = rotation / 180.0f * PI;
	fscanf(fi, "SCALE %f %f %f\n", &scale.x, &scale.y, &scale.z);
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(scale);
	model->loadModel(heightMap);
	return object;
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
	switch (key) {
	case VK_UP:	//MOVE UP
		if (bIsPressed) 
			m_pressedBtns |= BIT_MOVE_UP;
		else
			m_pressedBtns &= ~BIT_MOVE_UP;
		break;
	
	case VK_DOWN:	//MOVE DOWN
		if (bIsPressed) 
			m_pressedBtns |= BIT_MOVE_DOWN; 
		else 
			m_pressedBtns ^= BIT_MOVE_DOWN;
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

	case 'm':
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
