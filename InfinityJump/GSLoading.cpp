#include "stdafx.h"
#include "GSLoading.h"
#include "../3DEngine/Sprite.h"


shared_ptr<Sprite> GSLoading::m_background = NULL;
bool GSLoading::m_done = false;
int GSLoading::m_draw = 0;
int GSLoading::m_update = 0;

GSLoading::GSLoading()
{
}


GSLoading::~GSLoading()
{
}

void GSLoading::setDone(bool done)
{
	m_done = done;
}

void GSLoading::Init() {
	int exitcode = Singleton<SceneManager>::GetInstance()->Init(LOADINGSCENE_FILE);
	if (exitcode) return;
	auto m_objList = Singleton<SceneManager>::GetInstance()->m_objList;

	for (const auto obj : m_objList) {
		if (obj != NULL) {
			if (obj->getName() == "LOADING_BACKGROUND_0") {
				m_background = dynamic_pointer_cast<Sprite>(obj);
			}
		}
	}
}

void GSLoading::Enter() {
	m_textLoading = make_shared<Text>(string("LOADING ..."), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(300.0f, 300.0f), Vector2(2.0f, 2.0f));
}

void GSLoading::Loading(int index)
{
	switch (index) {
	case 0:
		Singleton<TextManager>::GetInstance()->Init();
		break;
	case 1:
		make_shared<GSMenu>()->Init();
		break;
	case 2:
		make_shared<GSSound>()->Init();
		break;
	case 3:
		make_shared<GSHelp>()->Init();
		break;
	case 4:
		make_shared<GSInfo>()->Init();
		break;
	case 5:
		make_shared<GSPlay>()->Init();
		break;
	case 6:
		make_shared<GSPause>()->Init();
		break;
	case 7:
		make_shared<GSGameOver>()->Init();
		break;
	case 8:
		make_shared<GSSelection>()->Init(LOAD_BUTTONS);
		break;
	case 9:
		make_shared<GSSelection>()->Init(LOAD_BACKGROUNDS);
		break;
	case 10:
		make_shared<GSSelection>()->Init(LOAD_PADS);
		break;
	case 11:
		make_shared<GSSelection>()->Init(LOAD_CHARACTERS, -1);
		break;
	case NUM_LOADING_STEP - 1:
		make_shared<GSSelection>()->Init(LOAD_FINISH);
		GSLoading::setDone(true);
		break;
	default:
		make_shared<GSSelection>()->Init(LOAD_CHARACTERS, index - 12);
		break;
	}
}

void GSLoading::Update(float dt) {
	if (m_update < m_draw && m_update < NUM_LOADING_STEP) {
		esLogMessage("Load asset %d: ", m_update);
		Loading(m_update);
		esLogMessage("Done\n");
		m_update++;
		m_iPercentageLoaded = m_update * 100 / NUM_LOADING_STEP;
	}

	m_textLoading->setText("LOADING: " + to_string(m_iPercentageLoaded) + "%");

	if (m_done) {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_MENU);
	}
}

void GSLoading::Draw() {
	if (m_update == m_draw) {
		++m_draw;
	}
	m_background->Draw();
	m_textLoading->Draw();
}
