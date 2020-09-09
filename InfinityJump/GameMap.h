#pragma once
#include "../3DEngine/3DEngine.h"

class GameMap
{
	std::shared_ptr<Sprite> m_background;
	std::shared_ptr<Sprite> m_normalPad;
	std::shared_ptr<Sprite> m_killerPad;

public:
	GameMap();
	GameMap(std::shared_ptr<Sprite> backgroundSprite,
		std::shared_ptr<Sprite> normalPadSprite,
		std::shared_ptr<Sprite> killerPadSprite);
	~GameMap();

	void setBackgroundSprite(std::shared_ptr<Sprite> sprite);
	void setNormalPadSprite(std::shared_ptr<Sprite> sprite);
	void setKillerPadSprite(std::shared_ptr<Sprite> sprite);

	std::shared_ptr<Sprite> getBackgroundSprite();
	std::shared_ptr<Sprite> getNormalPadSprite();
	std::shared_ptr<Sprite> getKillerPadSprite();
};

