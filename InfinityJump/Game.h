#pragma once
#include <deque>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Define.h"
#include "Character.h"
#include "Pad.h"
#include "ContactListener.h"

class ContactListener;

class Game
{
	std::vector<Object*> m_objList;
	Sprite* m_background;
	b2World* m_world;
	b2Body* m_groundBody;
	Character* m_character;
	Sprite* m_normalPadSprite;
	Sprite* m_killerPadSprite;
	std::deque<Pad*> m_pads;
	b2Fixture* m_characterFixture;
	GLfloat m_fSpawnTime;
	ContactListener* m_contactListener;

	void CreateNewPad(bool canKill);

public:
	Game();
	~Game();

	b2Fixture* getCharacterFixture();

	void Reset();
	int Init();
	void Draw();
	void Update(GLfloat dt);
	void Key(unsigned char key, bool bIsPressed);
	void TouchActionDown(int x, int y);
	void TouchActionUp(int x, int y);
	void TouchActionMove(int x, int y);
	void CleanUp();
};

