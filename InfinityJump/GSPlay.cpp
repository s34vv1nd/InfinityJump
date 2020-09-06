#include "stdafx.h"
#include "GSPlay.h"

shared_ptr<Sprite> GSPlay::m_background = NULL;
shared_ptr<Button> GSPlay::m_homeButton = NULL;
shared_ptr<b2World> GSPlay::m_world = NULL;
b2Body* GSPlay::m_groundBody = NULL;
shared_ptr<AnimSprite> GSPlay::m_characterSprite = NULL;
shared_ptr<Sprite> GSPlay::m_normalPadSprite = NULL;
shared_ptr<Sprite> GSPlay::m_killerPadSprite = NULL;
GLfloat GSPlay::m_fSpawnTime = 0;
shared_ptr<ContactListener> GSPlay::m_contactListener = NULL;

GSPlay::GSPlay()
{
}

GSPlay::~GSPlay()
{
}

void GSPlay::OnClickHomeButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_MENU);
	}
}

void GSPlay::Init()
{
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(PLAYSCENE_FILE);
	if (exitcode) return;


	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "MAP_BACKGROUND") {
				m_background = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "CHARACTER") {
				m_characterSprite = dynamic_pointer_cast<AnimSprite>(obj);
			}
			else if (obj->getName() == "PAD_NORMAL") {
				m_normalPadSprite = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "PAD_KILLER") {
				m_killerPadSprite = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "BUTTON_HOME") {
				m_homeButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickHomeButton);
			}
		}
	}

	m_world = make_shared<b2World>(WORLD_GRAVITY);
	m_contactListener = make_shared<ContactListener>();
	m_world->SetContactListener(m_contactListener.get());

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(Globals::screenWidth / 200.0f, 0.0f);
	m_groundBody = m_world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(Globals::screenWidth / 200.0f, 0.1f);
	m_groundBody->CreateFixture(&groundBox, 0.0f);

}

void GSPlay::Enter()
{
	Singleton<PadPool>::GetInstance()->Init(m_world, m_normalPadSprite, m_killerPadSprite, MAX_NUM_PAD);

	m_character = make_shared<Character>(m_world, m_characterSprite);

	m_pads.clear();
	for (int i = 0; i < 6; ++i) {
		float x = m_character->getPos2D().x + i * (m_normalPadSprite->getWidth());
		auto pad = Singleton<PadPool>::GetInstance()->createPad(false, { x, PAD_Y_COORD_LEVEL_0 }, { PAD_VELOCITY, 0.0f });
		m_pads.push_back(pad);
	}
	m_fSpawnTime = 0;

	m_textPoint = make_shared<Text>("Point: " + std::to_string(0), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(50.0f, 500.0f), Vector2(2.0f, 2.0f));
}

void GSPlay::Pause()
{
	m_isPaused = true;
	for (auto pad : m_pads) {
		pad->getBody()->SetLinearVelocity({ 0.0f, 0.0f });
	}
	m_character->Pause();
}

void GSPlay::Resume()
{
	m_isPaused = false;
	for (auto pad : m_pads) {
		pad->getBody()->SetLinearVelocity({ PAD_VELOCITY, 0.0f });
	}
	m_character->Resume();
}

void GSPlay::Exit()
{
	m_world->DestroyBody(m_character->getBody());
	m_character = NULL;
	while (!m_pads.empty()) {
		Singleton<PadPool>::GetInstance()->destroyPad(m_pads.front());
		m_pads.pop_front();
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
	m_homeButton->onClick(x, y, true);
}

void GSPlay::TouchActionMove(int x, int y)
{
}

void GSPlay::TouchActionUp(int x, int y)
{
	if (m_homeButton->onClick(x, y, false)) return;
	if (m_character->isJumpingFirst()) {
		m_character->JumpSecond();
	}
	else {
		m_character->JumpFirst();
	}
}

void GSPlay::Update(float dt)
{
	m_world->Step(dt, WORLD_VELOCITY_ITERATIONS, WORLD_POSITION_ITERATIONS);

	m_background->Update(dt);
	m_character->Update(dt);
	for (auto pad : m_pads) {
		pad->Update(dt);
	}
	m_homeButton->Update(dt);

	//printf("Number of pads: %d\n", m_pads.size());
	while (!m_pads.empty()) {
		auto& pad = m_pads.front();
		if (pad->getPos2D().x < -pad->getWidth()) {
			Singleton<PadPool>::GetInstance()->destroyPad(m_pads.front());
			m_pads.pop_front();
		}
		else break;
	}

	for (auto& pad : m_pads) {
		if (pad->isBehindCharacter(m_character) && !pad->getPassedCharacter()) {
			pad->setPassedCharacter(true);
			m_character->setPoint(m_character->getPoint() + 1);
			m_textPoint->setText("Point: " + std::to_string(m_character->getPoint()));
		}
	}

	if (!m_character->isDead()) {
		if (!m_isPaused) {
			m_fSpawnTime += dt;
			if (m_fSpawnTime > PAD_SPAWNTIME) {
				bool isKiller = false;
				if (m_pads.empty() || !m_pads.back()->isKiller()) isKiller = rand() % 2 == 1;
				int level = 0;
				if (!m_pads.back()->isKiller() || m_pads.back()->getLevel() == 0) level = rand() % 2;

				auto pad = Singleton<PadPool>::GetInstance()->createPad(
					isKiller, 
					{PAD_DEFAULT_X_COORD, level == 0 ? PAD_Y_COORD_LEVEL_0 : PAD_Y_COORD_LEVEL_1},
					{PAD_VELOCITY, 0.0f}
				);
				m_pads.push_back(pad);
				m_fSpawnTime = 0;
			}
		}
	}
	else {
		Pause();
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	for (const auto &pad : m_pads) {
		pad->Draw();
	}
	m_character->Draw();
	m_homeButton->Draw();
	m_textPoint->Draw();
}
