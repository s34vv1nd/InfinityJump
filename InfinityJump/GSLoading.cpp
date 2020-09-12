#include "stdafx.h"
#include "GSLoading.h"
#include "../3DEngine/Sprite.h"


shared_ptr<Sprite> GSLoading::m_background = NULL;
bool GSLoading::m_done = false;
//int GSLoading::m_draw = 0;
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

void GSLoading::Update(float dt) {
	if (m_update < NUM_LOADING_STEP) {
		esLogMessage("Load asset %d: ", m_update);
		Singleton<Game>::GetInstance()->LoadAssets(m_update);
		esLogMessage("Done\n");
		m_update++;
	} else {
		Singleton<GameStateMachine>::GetInstance()->PopState();
		Singleton<GameStateMachine>::GetInstance()->PushState(STATE_MENU);
	}
}

void GSLoading::Draw() {
	m_background->Draw();
}
