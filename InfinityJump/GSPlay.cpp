#include "stdafx.h"
#include "GSPlay.h"

shared_ptr<Sprite> GSPlay::m_background = NULL;
shared_ptr<Sprite> GSPlay::m_crown = NULL;
shared_ptr<Sprite> GSPlay::m_pause = NULL;
shared_ptr<Button> GSPlay::m_pauseButton_1 = NULL;
shared_ptr<Button> GSPlay::m_pauseButton_2 = NULL;
shared_ptr<Button> GSPlay::m_newGame = NULL;
shared_ptr<Button> GSPlay::m_exit = NULL;
shared_ptr<Button> GSPlay::m_restartButton = NULL;
shared_ptr<Button> GSPlay::m_resumeButton = NULL;
shared_ptr<Button> GSPlay::m_exitButton = NULL;
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

}
void GSPlay::OnClickPauseButton(int x, int y, bool isPressed)
{

}
void GSPlay::OnClickRestartButton(int x, int y, bool isPressed)
{
	if (!isPressed) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_PLAY);
	}
}
void GSPlay::OnClickResumeButton(int x, int y, bool isPressed)
{

}
void GSPlay::OnClickExitButton(int x, int y, bool isPressed)
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
				//m_background = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "PauseTextBoard") {
				m_pause = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "CrownTextBoard") {
				m_crown = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "CHARACTER") {
				//m_characterSprite = dynamic_pointer_cast<AnimSprite>(obj);
			}
			else if (obj->getName() == "PAD_NORMAL") {
				m_normalPadSprite = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "PAD_KILLER") {
				m_killerPadSprite = dynamic_pointer_cast<Sprite>(obj);
			}
			else if (obj->getName() == "BUTTON_HOME") {
				m_pauseButton_1 = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickHomeButton);
			}
			else if (obj->getName() == "BUTTON_PAUSE") {
				m_pauseButton_2 = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickPauseButton);
			}
			else if (obj->getName() == "RESTART_BUTTON") {
				m_restartButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickRestartButton);
			}
			else if (obj->getName() == "NEWGAME") {
				m_newGame = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickRestartButton);
			}
			else if (obj->getName() == "RESUME_BUTTON") {
				m_resumeButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickResumeButton);
			}
			else if (obj->getName() == "EXIT_BUTTON") {
				m_exitButton = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickExitButton);
			}
			else if (obj->getName() == "EXIT") {
				m_exit = make_shared<Button>(dynamic_pointer_cast<Sprite>(obj), &GSPlay::OnClickExitButton);
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
	groundBox.SetAsBox(Globals::screenWidth / 200.0f, 0.2f);
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
	m_character->setPos2D(CHARACTER_DEFAULT_X_COORD, CHARACTER_INITIAL_Y_COORD);

	m_pads.clear();
	for (int i = 0; i < NUM_INITIAL_PAD; ++i) {
		float x = PAD_FIRST_X_COORD + i * (m_normalPadSprite->getWidth());
		auto pad = Singleton<PadPool>::GetInstance()->createPad(false, { x, PAD_Y_COORD_LEVEL_0 }, { PAD_VELOCITY, 0.0f });
		m_pads.push_back(pad);
	}
	m_fSpawnTime = 0;

	//set highscore
	m_character->getCurrentHighScore();
	m_textHighScore = make_shared<Text>("High Score: " + std::to_string(m_character->getHighScore()),
		Vector4(1.0f, 0.5f, 0.0f, 1.0f), Vector2(290.0f, 550.0f), Vector2(2.0f, 2.0f));

	m_textPoint = make_shared<Text>(std::to_string(0), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(465.0f, 500.0f), Vector2(2.0f, 2.0f));
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

}

void GSPlay::TouchActionDown(int x, int y)
{
	m_pauseButton_1->onClick(x, y, true);

}

void GSPlay::TouchActionMove(int x, int y)
{
}

void GSPlay::TouchActionUp(int x, int y)
{
	if (m_pauseButton_1->onClick(x, y, false)) {
		Pause();
		return;
	}
	if (m_isPaused) {
		if (!m_character->isDead()) {
			if (m_resumeButton->onClick(x, y, false)) {
				Resume();
				return;
			}
			if (m_restartButton->onClick(x, y, false)) return;
			if (m_exitButton->onClick(x, y, false)) return;
		}
		else {
			if (m_newGame->onClick(x, y, false)) return;
			if (m_exit->onClick(x, y, false)) return;
		}
	}
	else {
		if (m_character->isJumpingFirst()) {
			m_character->JumpSecond();
		}
		else {
			m_character->JumpFirst();
		}
	}
}

void GSPlay::Update(float dt)
{
	if (!m_isPaused) {
		m_world->Step(dt, WORLD_VELOCITY_ITERATIONS, WORLD_POSITION_ITERATIONS);
		m_background->Update(dt);
		m_character->Update(dt);
		for (auto pad : m_pads) {
			pad->Update(dt);
		}
	}
	else {
		if (m_character->isDead()) {
			m_world->Step(dt, WORLD_VELOCITY_ITERATIONS, WORLD_POSITION_ITERATIONS);
			m_character->Update(dt);
		}
	}
	m_pauseButton_1->Update(dt);

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

	if (!m_character->isDead()) {
		if (!m_isPaused) {
			m_fSpawnTime += dt;
			if (m_fSpawnTime > PAD_SPAWNTIME) {
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
					{ PAD_DEFAULT_X_COORD, y },
					{ PAD_VELOCITY, 0.0f }
				);
				m_pads.push_back(pad);
				m_fSpawnTime = 0;
			}
		}
	}
	else {
		if (m_character->getPoint() > m_character->getHighScore())
			m_character->setHighScore(m_character->getPoint());
		Pause();
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	for (const auto &pad : m_pads)
		if (pad->getInUse()) {
			pad->Draw();
		}
	m_character->Draw();

	m_pauseButton_1->Draw();
	m_textHighScore->Draw();
	m_textPoint->Draw();
	if (m_isPaused) {
		m_pauseButton_2->Draw();
		if (!m_character->isDead()) {
			m_crown->Draw();
			m_pause->Draw();
			m_restartButton->Draw();
			m_resumeButton->Draw();
			m_exitButton->Draw();
		}
		else {
			m_newGame->Draw();
			m_exit->Draw();
		}

	}
}
