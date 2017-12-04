#include "SpaceMap.hpp"

#include "GameSingleton.hpp"

SpaceMap::SpaceMap(oe::EntityManager& manager)
	: oe::Entity(manager)
{
	setPositionZ(-1000);
	for (I32 i = -1; i < 2; i++)
	{
		for (I32 j = -1; j < 2; j++)
		{
			mTiles.push_back(new oe::SpriteComponent(*this));
			mTiles.back()->setTexture(GameSingleton::mTilesetTexture);
			mTiles.back()->setPosition(i * 2048.f, j * 2048.f);
		}
	}
	mLastCoords = oe::Vector2i(0, 0);
	setPosition(0, 0);
}

SpaceMap::~SpaceMap()
{
	for (U32 i = 0; i < mTiles.size(); i++)
	{
		delete mTiles[i];
	}
}

void SpaceMap::update(oe::Time dt)
{
	oe::Vector2i p = oe::Vector2i(I32(GameSingleton::mPlayerShip->getPosition().x / 2048.f), I32(GameSingleton::mPlayerShip->getPosition().y / 2048.f));
	if (GameSingleton::mPlayerShip->getPosition().x < 0)
		p.x--;
	if (GameSingleton::mPlayerShip->getPosition().y < 0)
		p.y--;
	if (mLastCoords != p)
	{
		mLastCoords = p;
		setPosition(mLastCoords.x * 2048.f, mLastCoords.y * 2048.f);
	}
}
