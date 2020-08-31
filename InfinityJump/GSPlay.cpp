#include "stdafx.h"
#include "GSPlay.h"

std::vector<Object*> GSPlay::m_objList = std::vector<Object*>();
Sprite* GSPlay::m_background = NULL;
b2World* GSPlay::m_world = NULL;
b2Body* GSPlay::m_groundBody = NULL;
AnimSprite* GSPlay::m_characterSprite = NULL;
Sprite* GSPlay::m_normalPadSprite = NULL;
Sprite* GSPlay::m_killerPadSprite = NULL;
GLfloat GSPlay::m_fSpawnTime = 0;
ContactListener* GSPlay::m_contactListener = NULL;

GSPlay::GSPlay()
{
}

GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(PLAYSCENE_FILE);
	if (exitcode) return;

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
				m_characterSprite = dynamic_cast<AnimSprite*>(obj);
				
			}
			else if (obj->getName() == "PAD_NORMAL") {
				m_normalPadSprite = dynamic_cast<Sprite*>(obj);
			}
			else if (obj->getName() == "PAD_KILLER") {
				m_killerPadSprite = dynamic_cast<Sprite*>(obj);
			}
		}
	}
}

void GSPlay::Enter()
{
	m_character = new Character(m_world, m_characterSprite);

	m_pads.clear();
	for (int i = 0; i < 6; ++i) {
		CreateNewPad(false, 0);
		Pad* pad = m_pads.back();
		int width = pad->getWidth();
		pad->setPos2D(m_character->getPos2D().x + i * width, pad->getPos2D().y);
		//printf("Pad: x = %f , y = %f\n", pad->getPos2D().x, pad->getPos2D().y);
		pad->getBody()->SetTransform({
			(pad->getPos2D().x + pad->getWidth() / 2.0f) / 100.0f,
			(pad->getPos2D().y + pad->getHeight() / 2.0f) / 100.0f
			}, 0);
	}
	m_fSpawnTime = 0;
}

void GSPlay::Pause()
{
	m_isPaused = true;
	for (Pad* pad : m_pads) {
		pad->getBody()->SetLinearVelocity({ 0.0f, 0.0f });
	}
	m_character->Pause();
}

void GSPlay::Resume()
{
	m_isPaused = false;
	for (Pad* pad : m_pads) {
		pad->getBody()->SetLinearVelocity({ PAD_VELOCITY, 0.0f });
	}
	m_character->Resume();
}

void GSPlay::Exit()
{
	SAFE_DEL(m_character);
	while (!m_pads.empty()) {
		SAFE_DEL(m_pads.back());
		m_pads.pop_back();
	}
}

void GSPlay::Key(unsigned char key, bool bIsPressed)
{
	if (!bIsPressed) return;

	switch (key) {
	case 'J':
		if (m_character->isJumpingFirst()) {
			m_character->JumpSecond();
		}
		else {
			m_character->JumpFirst();
		}
		break;
	case 'P':
		if (!m_isPaused) {
			Pause();
		}
		else {
			Resume();
		}
		break;
	default:
		//Singleton<SceneManager>::GetInstance()->Key(key, bIsPressed);
		break;
	}
}

void GSPlay::TouchActionDown(int x, int y)
{
}

void GSPlay::TouchActionUp(int x, int y)
{
}

void GSPlay::TouchActionMove(int x, int y)
{
}

void GSPlay::CreateNewPad(bool canKill, int level)
{
	Sprite* sprite = new Sprite(canKill ? *m_killerPadSprite : *m_normalPadSprite);
	Pad* pad = new Pad(m_world, sprite, canKill, level);
	pad->setPos2D(pad->getPos2D().x, level == 1 ? PAD_HEIGHT_LEVEL_1 : PAD_HEIGHT_LEVEL_0);
	pad->getBody()->SetTransform({
			(pad->getPos2D().x + pad->getWidth() / 2.0f) / 100.0f,
			(pad->getPos2D().y + pad->getHeight() / 2.0f) / 100.0f
		}, 0);
	//printf("Pad: x = %f , y = %f\n", pad->getPos2D().x, pad->getPos2D().y);
	m_pads.push_back(pad);
	SAFE_DEL(sprite);
}

void GSPlay::Update(float dt)
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
		if (!m_isPaused) {
			m_fSpawnTime += dt;
			if (m_fSpawnTime > PAD_SPAWNTIME) {
				bool canKill = false;
				if (m_pads.empty() || !m_pads.back()->isKiller()) canKill = rand() % 2;
				int level = 0;
				if (!m_pads.back()->isKiller() || m_pads.back()->getLevel() == 0) level = rand() % 2;
				CreateNewPad(canKill, level);
				m_fSpawnTime = 0;
			}
		}
	}
	else {
		Pause();
	}

	m_world->Step(dt, WORLD_VELOCITY_ITERATIONS, WORLD_POSITION_ITERATIONS);
	m_background->Update(dt);
	m_character->Update(dt);
	for (Pad* pad : m_pads) {
		pad->Update(dt);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	for (Pad* pad : m_pads) {
		//printf("Pad: x = %f , y = %f\n", pad->getPos2D().x, pad->getPos2D().y);
		pad->Draw();
	}
	m_character->Draw();
}
