#pragma once
#include <queue>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "GameStateBase.h"
#include "Box2D/Box2D.h"
#include "Pad.h"
#include "PadPool.h"
#include "Character.h"
#include "ContactListener.h"
#include "Button.h"
#include "Text.h"

class ContactListener;

class GSPlay : public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static shared_ptr<Sprite> m_crown;
	static shared_ptr<Sprite> m_pause;
	static shared_ptr<Button> m_pauseButton_1;
	static shared_ptr<Button> m_pauseButton_2;
	static shared_ptr<Button> m_restartButton;
	static shared_ptr<Button> m_resumeButton;
	static shared_ptr<Button> m_exitButton;
	static shared_ptr<Button> m_newGame;
	static shared_ptr<Button> m_exit;



	static std::shared_ptr<b2World> m_world;
	static b2Body* m_groundBody;
	static std::shared_ptr<AnimSprite> m_characterSprite;
	static std::shared_ptr<Sprite> m_normalPadSprite;
	static std::shared_ptr<Sprite> m_killerPadSprite;
	static GLfloat m_fSpawnTime;
	static std::shared_ptr<ContactListener> m_contactListener;

	std::shared_ptr<Character> m_character = NULL;
	std::deque<std::shared_ptr<Pad>> m_pads = std::deque<std::shared_ptr<Pad>>();

	std::shared_ptr<Text> m_textPoint = NULL;
	std::shared_ptr<Text> m_textHighScore = NULL;

	static void OnClickHomeButton(int x, int y, bool isPressed);
	static void OnClickPauseButton(int x, int y, bool isPressed);
	static void OnClickExitButton(int x, int y, bool isPressed);
	static void OnClickRestartButton(int x, int y, bool isPressed);
	static void OnClickResumeButton(int x, int y, bool isPressed);
	static void OnClickExit(int x, int y, bool isPressed);
	static void OnClickNewGame(int x, int y, bool isPressed);

public:
	GSPlay();
	~GSPlay();

	void Init();
	void Enter();
	void Pause();
	void Resume();
	void Exit();

	void Key(unsigned char key, bool bIsPressed);
	void TouchActionDown(int x, int y);
	void TouchActionMove(int x, int y);
	void TouchActionUp(int x, int y);

	void Update(float dt);
	void Draw();
};

