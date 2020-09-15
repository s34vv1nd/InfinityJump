#include "stdafx.h"
#include "GSPlay.h"

shared_ptr<Sprite> GSPlay::m_background = NULL;
shared_ptr<Button> GSPlay::m_pauseButton1 = NULL;
shared_ptr<Button> GSPlay::m_pauseButton2 = NULL;
shared_ptr<b2World> GSPlay::m_world = NULL;
b2Body* GSPlay::m_groundBody = NULL;
shared_ptr<AnimSprite> GSPlay::m_characterSprite = NULL;
shared_ptr<Sprite> GSPlay::m_normalPadSprite = NULL;
shared_ptr<Sprite> GSPlay::m_killerPadSprite = NULL;
shared_ptr<ContactListener> GSPlay::m_contactListener = NULL;

GSPlay::GSPlay()
{
}

GSPlay::~GSPlay()
{
}

std::shared_ptr<Character> GSPlay::getCharacter()
{
	return m_character;
}

float GSPlay::getTimePerSpawn()
{
	return m_fTimePerSpawn;
}

void GSPlay::setTimePerSpawn(float time)
{
	m_fTimePerSpawn = time;
}

void GSPlay::OnClickPauseButton1(int x, int y, bool isPressed, void* context)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_PAUSE);
	}
}

void GSPlay::OnClickPauseButton2(int x, int y, bool isPressed, void* context)
{

}
void GSPlay::Init()
{
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(PLAYSCENE_FILE);
	if (exitcode) return;

	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;
	for (auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "BUTTON_PAUSE_1") {
				m_pauseButton1 = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickPauseButton1);
			}
			else if (obj->getName() == "BUTTON_PAUSE_2") {
				m_pauseButton2 = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickPauseButton2);
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
	groundBox.SetAsBox(Globals::screenWidth / 200.0f, 0.0f);
	m_groundBody->CreateFixture(&groundBox, 0.0f);
}

void GSPlay::Enter()
{
	m_background = GSSelection::getCurrentMap()->getBackgroundSprite();
	m_normalPadSprite = GSSelection::getCurrentMap()->getNormalPadSprite();
	m_killerPadSprite = GSSelection::getCurrentMap()->getKillerPadSprite();
	Singleton<PadPool>::GetInstance()->Init(m_world, m_normalPadSprite, m_killerPadSprite, MAX_NUM_PAD);

	m_characterSprite = GSSelection::getCurrentCharacterSprite();
	m_character = make_shared<Character>(m_world, m_characterSprite);
	m_character->Resume();
	m_character->setPos2D({ CHARACTER_DEFAULT_X_COORD + m_character->getWidth(), CHARACTER_INITIAL_Y_COORD });

	m_pads.clear();
	for (int i = 0; i < NUM_INITIAL_PAD; ++i) {
		float x = PAD_FIRST_X_COORD + i * (m_normalPadSprite->getWidth() + 10.0f);
		auto pad = Singleton<PadPool>::GetInstance()->createPad(false, 0, { x, PAD_Y_COORD_LEVEL_0 }, { PAD_VELOCITY_X, 0.0f });
		m_pads.push_back(pad);
	}
	m_fTime = 0;
	m_fTimePerSpawn = PAD_SPAWNTIME;

	//set highscore
	m_character->getCurrentHighScore();
	m_textHighScore = make_shared<Text>("High Score: " + std::to_string(m_character->getHighScore()),
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(290.0f, 550.0f), Vector2(2.0f, 2.0f));

	m_textPoint = make_shared<Text>(std::to_string(0), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(100.0f, 550.0f), Vector2(2.0f, 2.0f));
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
		pad->getBody()->SetLinearVelocity({ PAD_VELOCITY_X, 0.0f });
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

void GSPlay::TouchActionUp(int x, int y)
{
	if (!m_isPaused && m_pauseButton1->onClick(x, y, false, this)) return;
	if (m_isPaused && m_pauseButton2->onClick(x, y, false, this)) return;
	if (m_isPaused) return;

	if (m_character->isJumpingFirst() && !m_character->isJumpingSecond()) {
		m_character->JumpSecond();
	}
	else if (!m_character->isJumpingFirst() && !m_character->isJumpingSecond()) {
		m_character->JumpFirst();
	}
}

void GSPlay::Update(float dt)
{
	if (m_character->isDead()) {
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_GAMEOVER);
	}

	if (!m_isPaused) {
		m_world->Step(dt, WORLD_VELOCITY_ITERATIONS, WORLD_POSITION_ITERATIONS);
		m_background->Update(dt);
		m_character->Update(dt);
		for (auto pad : m_pads) {
			pad->Update(dt);
		}
		m_pauseButton1->Update(dt);

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
				m_textPoint->setText(std::to_string(m_character->getPoint()));
			}
		}

		m_fTime += dt;
		if (m_fTime > m_fTimePerSpawn) {
			bool isKiller = false;
			if (m_pads.empty() || !m_pads.back()->isKiller()) isKiller = rand() % 2 == 1;
			int level = 0;
			if (!m_pads.back()->isKiller() || m_pads.back()->getLevel() == 0) level = rand() % 3;
			float y;
			if (level == 0) y = PAD_Y_COORD_LEVEL_0;
			else if (level == 1) y = PAD_Y_COORD_LEVEL_1;
			else {
				y = PAD_Y_COORD_LEVEL_2; isKiller = false;
			} 
			auto pad = Singleton<PadPool>::GetInstance()->createPad(
				isKiller,
				level,
				{ PAD_DEFAULT_X_COORD, y },
				{ PAD_VELOCITY_X, 0.0f }
			);
			m_pads.push_back(pad);
			m_fTime = 0;
		}
	}
}

void GSPlay::UpdateWhenGameOver(float dt)
{
	m_world->Step(dt, WORLD_VELOCITY_ITERATIONS, WORLD_POSITION_ITERATIONS);
	m_character->Update(dt);
	if (m_character->getPoint() > m_character->getHighScore())
		m_character->setHighScore(m_character->getPoint());
	Pause();
}

void GSPlay::Draw()
{
	//printf("Character pos: y = %f , height = %f\n", m_character->getPos2D().y, m_character->getHeight());
	m_background->Draw();
	for (const auto &pad : m_pads)
		if (pad->getInUse()) {
			pad->Draw();
			//printf("Pad pos: y = %f , height = %f\n", pad->getPos2D().y, pad->getHeight());
		}
	m_character->Draw();

	m_pauseButton1->Draw();
	m_textHighScore->Draw();
	m_textPoint->Draw();
	if (m_isPaused) {
		m_pauseButton2->Draw();
	}
}
