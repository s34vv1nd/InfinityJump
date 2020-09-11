#include "stdafx.h"
#include "PadPool.h"

void PadPool::Init(std::shared_ptr<b2World> world, std::shared_ptr<Sprite> normalPadSprite, std::shared_ptr<Sprite> killerPadSprite, int numPads)
{
	m_normalPadPool.clear();
	m_killerPadPool.clear();
	for (int i = 0; i < numPads; ++i) {
		shared_ptr<Pad> normalPad = make_shared<Pad>(world, normalPadSprite, 0);
		normalPad->setID(i);
		m_normalPadPool.push_back(normalPad);
		shared_ptr<Pad> killerPad = make_shared<Pad>(world, killerPadSprite, 1);
		killerPad->setID(numPads + i);
		m_killerPadPool.push_back(killerPad);
	}
}

std::shared_ptr<Pad> PadPool::createPad(const bool isKiller, int level, const Vector2 position, const b2Vec2 velocity)
{
	auto& pool = (isKiller ? m_killerPadPool : m_normalPadPool);
	auto& pad = pool.front();
	assert(!pad->getInUse());

	pool.push_back(pool.front());
	pool.pop_front();
	pad->setLevel(level);
	pad->getBody()->SetLinearVelocity(velocity);
	pad->setPos2D({ position.x, position.y });
	pad->setPassedCharacter(false);
	pad->setInUse(true);

	b2Body* body = pad->getBody();
	shared_ptr<GSPlay> currentPlayScene = static_pointer_cast<GSPlay>(Singleton<GameStateMachine>::GetInstance()->CurrentState());
	int currentPoint = currentPlayScene->getCharacter()->getPoint();
	float vx = body->GetLinearVelocity().x;
	float _vy = (currentPoint >= PAD_MOVING_Y_POINT) ? PAD_VELOCITY_Y : 0;
	float vy = (rand() % 3 == 0) ? _vy : 0;
	currentPlayScene->setTimePerSpawn(PAD_SPAWNTIME / pow(PAD_SPAWNTIME_DECREASE_RATE, currentPoint / NUM_PAD_PER_INCREASE_SPEED));
	body->SetLinearVelocity({ vx, vy });
	return pad;
}

void PadPool::destroyPad(std::shared_ptr<Pad> pad)
{
	//printf("Destroy pad at: x = %f , y = %f\n", pad->getPos2D().x, pad->getPos2D().y);
	pad->getBody()->SetLinearVelocity({ 0.0f, 0.0f });
	pad->setPos2D({ PAD_DEFAULT_X_COORD, PAD_Y_COORD_LEVEL_0 });
	pad->setPassedCharacter(false);
	pad->setInUse(false);
}

void PadPool::CleanUp()
{
	m_normalPadPool.clear();
	m_killerPadPool.clear();
}
