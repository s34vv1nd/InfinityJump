#pragma once
#include <deque>
#include "../3DEngine/3DEngine.h"
#include "Pad.h"

class PadPool
{
	std::deque<std::shared_ptr<Pad>> m_normalPadPool;
	std::deque<std::shared_ptr<Pad>> m_killerPadPool;

public:
	void Init(std::shared_ptr<b2World> world, std::shared_ptr<Sprite> normalPadSprite, std::shared_ptr<Sprite> killerPadSprite, int numPads);
	std::shared_ptr<Pad> createPad(const bool isKiller, const Vector2 position, const b2Vec2 velocity);
	void destroyPad(std::shared_ptr<Pad> pad);
	void CleanUp();
};

