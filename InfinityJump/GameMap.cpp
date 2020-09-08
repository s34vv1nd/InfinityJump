#include "stdafx.h"
#include "GameMap.h"


GameMap::GameMap():
	m_background(NULL),
	m_normalPad(NULL),
	m_killerPad(NULL)
{
}

GameMap::GameMap(std::shared_ptr<Sprite> backgroundSprite, std::shared_ptr<Sprite> normalPadSprite, std::shared_ptr<Sprite> killerPadSprite):
	m_background(backgroundSprite),
	m_normalPad(normalPadSprite),
	m_killerPad(killerPadSprite)
{
}


GameMap::~GameMap()
{
}

void GameMap::setBackgroundSprite(std::shared_ptr<Sprite> sprite)
{
	m_background = sprite;
}

void GameMap::setNormalPadSprite(std::shared_ptr<Sprite> sprite)
{
	m_normalPad = sprite;
}

void GameMap::setKillerPadSprite(std::shared_ptr<Sprite> sprite)
{
	m_killerPad = sprite;
}

std::shared_ptr<Sprite> GameMap::getBackgroundSprite()
{
	return m_background;
}

std::shared_ptr<Sprite> GameMap::getNormalPadSprite()
{
	return m_normalPad;
}

std::shared_ptr<Sprite> GameMap::getKillerPadSprite()
{
	return m_killerPad;
}
