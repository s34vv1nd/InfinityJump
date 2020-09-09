#pragma once
#include "GameStateBase.h"
#include "Character.h"
#include "Button.h"
#include "GameMap.h"

class GSSelection :
	public GameStateBase
{
	static std::shared_ptr<Sprite> m_background;
	static std::shared_ptr<Button> m_homeButton;
	static std::shared_ptr<Button> m_leftArrowButton1;
	static std::shared_ptr<Button> m_rightArrowButton1;
	static std::shared_ptr<Button> m_leftArrowButton2;
	static std::shared_ptr<Button> m_rightArrowButton2;

	static std::vector<std::shared_ptr<AnimSprite>> m_characterSprites;
	static int m_currentCharacterSprite;

	static std::vector<std::shared_ptr<GameMap>> m_gameMaps;
	static int m_currentMap;

	static void OnClickHomeButton(int x, int y, bool isPressed);
	static void OnClickLeftArrowButton1(int x, int y, bool isPressed);
	static void OnClickRightArrowButton1(int x, int y, bool isPressed);
	static void OnClickLeftArrowButton2(int x, int y, bool isPressed);
	static void OnClickRightArrowButton2(int x, int y, bool isPressed);

public:
	GSSelection();
	~GSSelection();

	static std::shared_ptr<AnimSprite> getCurrentCharacterSprite();
	static std::shared_ptr<GameMap> getCurrentMap();

	virtual void Init();
	virtual void Enter();
	virtual void Exit() {}
	virtual void Pause() {}
	virtual void Resume() {}

	virtual void Key(unsigned char key, bool bIsPressed) {}
	virtual void TouchActionDown(int x, int y) {}
	virtual void TouchActionMove(int x, int y) {}
	virtual void TouchActionUp(int x, int y);

	virtual void Update(float dt);
	virtual void Draw();
};

