#include "stdafx.h"
#include "Game.h"
#include "../3DEngine/AnimSprite.h"


Game::Game():
	m_objList(std::vector<Object*>()),
	m_background(NULL),
	m_world(NULL),
	m_groundBody(NULL),
	m_character(NULL),
	m_fSpawnTime(0)
{
}

Game::~Game()
{
	CleanUp();
}

b2Fixture* Game::getCharacterFixture() {
	return m_characterFixture;
}

void Game::Reset()
{
}

int Game::Init()
{
	Singleton<ResourceManager>::GetInstance()->Init(RM_TXT_FILE);
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(SM_TXT_FILE);
	if (exitcode) return exitcode;

	m_world = new b2World(WORLD_GRAVITY);
	m_contactListener = new ContactListener();
	m_world->SetContactListener(m_contactListener);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(Globals::screenWidth / 200.0, 0.0f);
	m_groundBody = m_world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(Globals::screenWidth / 200.0, 0.1);
	m_groundBody->CreateFixture(&groundBox, 0.0);

	m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (Object* obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "MAP_BACKGROUND") {
				m_background = dynamic_cast<Sprite*>(obj);
			}
			else if (obj->getName() == "CHARACTER") {
				m_character = new Character(m_world, dynamic_cast<AnimSprite*>(obj));
				m_characterFixture = &m_character->getBody()->GetFixtureList()[0];
			}
			else if (obj->getName() == "PAD_NORMAL") {
				m_normalPadSprite = dynamic_cast<Sprite*>(obj);
			}
			else if (obj->getName() == "PAD_KILLER") {
				m_killerPadSprite = dynamic_cast<Sprite*>(obj);
			}
		}
	}

	for (int i = 0; i < 6; ++i) {
		CreateNewPad(false);
		Pad* pad = m_pads.back();
		int width = pad->getWidth();
		pad->setPos2D(m_character->getPos2D().x + i * width, pad->getPos2D().y);
		printf("Pad: x = %f , y = %f\n", pad->getPos2D().x, pad->getPos2D().y);
		pad->getBody()->SetTransform({ 
			(pad->getPos2D().x + pad->getWidth() / 2.0f) / 100.0f, 
			(pad->getPos2D().y + pad->getHeight() / 2.0f) / 100.0f 
			}, 0);
	}

	return 0;
}

void Game::Draw()
{
	m_background->Draw();
	for (Pad* pad : m_pads) {
		//printf("Pad: x = %f , y = %f\n", pad->getPos2D().x, pad->getPos2D().y);
		pad->Draw();
	}
	m_character->Draw();
}

void Game::CreateNewPad(bool canKill)
{
	Sprite* sprite = new Sprite(canKill ? *m_killerPadSprite : *m_normalPadSprite);
	Pad* pad = new Pad(m_world, sprite, canKill);
	printf("Pad: x = %f , y = %f\n", pad->getPos2D().x, pad->getPos2D().y);
	m_pads.push_back(pad);
	SAFE_DEL(sprite);
}

void Game::Update(GLfloat dt)
{
	//printf("Number of pads: %d\n", m_pads.size());
	while (!m_pads.empty()) {
		Pad* pad = m_pads.front();
		if (pad->getPos2D().x < -pad->getWidth()) {
			SAFE_DEL(pad);
			m_pads.pop_front();
		}
		else break;
	}

	if (!m_character->isDead()) {
		m_fSpawnTime += dt;
		if (m_fSpawnTime > PAD_SPAWNTIME) {
			bool canKill = false;
			if (m_pads.empty() || !m_pads.back()->isKiller()) canKill = rand() % 2;
			CreateNewPad(canKill);
			m_fSpawnTime = 0;
		}
	}
	else {
		for (Pad* pad : m_pads) {
			pad->getBody()->SetLinearVelocity({ 0.0f, 0.0f });
		}
	}
	
	m_world->Step(dt, WORLD_VELOCITY_ITERATIONS, WORLD_POSITION_ITERATIONS);
	m_background->Update(dt);
	m_character->Update(dt);
	for (Pad* pad : m_pads) {
		pad->Update(dt);
	}
}

void Game::Key(unsigned char key, bool bIsPressed)
{
	if (!bIsPressed) return;

	switch (key) {
	case 'J':
		if (m_character->isJumpingFirst()) {
			m_character->JumpSecond();
		} else {
			m_character->JumpFirst();
		}
		break;
	/*case 'R':
		CleanUp();
		Reset();
		Init();
		break;*/
	default:
		//Singleton<SceneManager>::GetInstance()->Key(key, bIsPressed);
		break;
	}
}

void Game::TouchActionDown(int x, int y)
{
	
}

void Game::TouchActionUp(int x, int y)
{
}

void Game::TouchActionMove(int x, int y)
{
}

void Game::CleanUp()
{
	Singleton<SceneManager>::GetInstance()->CleanUp();
	Singleton<ResourceManager>::GetInstance()->CleanUp();
	//SAFE_DEL(m_background);
	//SAFE_DEL(m_character);
	//SAFE_DEL(m_characterFixture);
	//SAFE_DEL(m_contactListener);
	//SAFE_DEL(m_normalPadSprite);
	//SAFE_DEL(m_killerPadSprite);
	m_pads.clear();
	m_objList.clear();
	m_fSpawnTime = 0;
}
