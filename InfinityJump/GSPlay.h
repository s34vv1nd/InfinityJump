#pragma once
#include <queue>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Box2D/Box2D.h"
#include "Define.h"
#include "GameStateBase.h"
#include "Pad.h"
#include "PadPool.h"
#include "Character.h"
#include "ContactListener.h"
#include "Button.h"
#include "Text.h"

class ContactListener;
class Character;
class Pad;
class Button;

class GSPlay : public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static shared_ptr<Button> m_pauseButton1;
	static shared_ptr<Button> m_pauseButton2;

	static std::shared_ptr<b2World> m_world;
	static b2Body* m_groundBody;
	static std::shared_ptr<AnimSprite> m_characterSprite;
	static std::shared_ptr<Sprite> m_normalPadSprite;
	static std::shared_ptr<Sprite> m_killerPadSprite;
	GLfloat m_fTime;
	GLfloat m_fTimePerSpawn;
	static std::shared_ptr<ContactListener> m_contactListener;

	std::shared_ptr<Character> m_character = NULL;
	std::deque<std::shared_ptr<Pad>> m_pads = std::deque<std::shared_ptr<Pad>>();

	std::shared_ptr<Text> m_textPoint = NULL;
	std::shared_ptr<Text> m_textHighScore = NULL;

	static void OnClickPauseButton1(int x, int y, bool isPressed, void* context);
	static void OnClickPauseButton2(int x, int y, bool isPressed, void* context);

public:
	GSPlay();
	~GSPlay();

	std::shared_ptr<Character> getCharacter();
	float getTimePerSpawn();
	void setTimePerSpawn(float time);

	void Init();
	void Enter();
	void Pause();
	void Resume();
	void Exit();

	void Key(unsigned char key, bool bIsPressed) {}
	void TouchActionDown(int x, int y) {}
	void TouchActionMove(int x, int y) {}
	void TouchActionUp(int x, int y);

	void Update(float dt);
	void UpdateWhenGameOver(float dt);
	void Draw();
};

