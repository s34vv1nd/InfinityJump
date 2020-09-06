#pragma once
#include <queue>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "GameStateBase.h"
#include "Box2D/Box2D.h"
#include "Pad.h"
#include "Character.h"
#include "ContactListener.h"
#include "PadPool.h"
#include "Button.h"
#include "Text.h"

class ContactListener;

class GSPlay : public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static shared_ptr<Button> m_homeButton;

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

	static void OnClickHomeButton(int x, int y, bool isPressed);

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

