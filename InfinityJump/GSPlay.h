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
#include "Button.h"

class ContactListener;

class GSPlay : public GameStateBase
{
	static shared_ptr<Sprite> m_background;
	static shared_ptr<Button> m_homeButton;

	static shared_ptr<b2World> m_world;
	static b2Body* m_groundBody;
	static shared_ptr<AnimSprite> m_characterSprite;
	static shared_ptr<Sprite> m_normalPadSprite;
	static shared_ptr<Sprite> m_killerPadSprite;
	static GLfloat m_fSpawnTime;
	static shared_ptr<ContactListener> m_contactListener;

	shared_ptr<Character> m_character = NULL;
	std::deque<shared_ptr<Pad>> m_pads = std::deque<std::shared_ptr<Pad>>();

	void CreateNewPad(bool canKill, int level);

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

