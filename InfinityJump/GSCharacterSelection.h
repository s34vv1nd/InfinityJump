#pragma once
#include "GameStateBase.h"
#include "Character.h"
#include "Button.h"

class GSCharacterSelection :
	public GameStateBase
{
	static std::shared_ptr<Sprite> m_background;
	static std::shared_ptr<Button> m_homeButton;
	static std::shared_ptr<Button> m_leftArrowButton;
	static std::shared_ptr<Button> m_rightArrowButton;

	static std::vector<std::shared_ptr<AnimSprite>> m_characterSprites;
	static int m_currentCharacterSprite;

	static void OnClickHomeButton(int x, int y, bool isPressed);
	static void OnClickLeftArrowButton(int x, int y, bool isPressed);
	static void OnClickRightArrowButton(int x, int y, bool isPressed);

public:
	GSCharacterSelection();
	~GSCharacterSelection();

	static std::shared_ptr<AnimSprite> getCurrentCharacterSprite();

	virtual void Init();
	virtual void Enter() {}
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

