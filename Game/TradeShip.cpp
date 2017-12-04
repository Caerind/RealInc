#include "TradeShip.hpp"

#include "GameSingleton.hpp"

#include "GameConfig.hpp"

#include "../Engine/Core/World.hpp"

TradeShip::TradeShip(oe::EntityManager& manager)
	: Ship(manager, 2)
{
	setPositionZ(-1);

	mShip.setTexture(GameSingleton::mTradeShipTexture);
	mShip.setTextureRect(sf::IntRect(0, 0, 106, 208));
	mShip.setPosition(-53, -104);
	mShip.setPositionZ(0);

	mProp.setTexture(GameSingleton::mTradeShipTexture);
	mProp.setTextureRect(sf::IntRect(0, 0, 1, 1));
	mProp.setPosition(-53 + 1, -104 + 74);
	mProp.setPositionZ(1);

	mShield.setTexture(GameSingleton::mTradeShipTexture);
	mShield.setTextureRect(sf::IntRect(320, 4, 148, 233));
	mShield.setPosition(-74, -116);

	mCollisionSize = GameConfig::getF("trader-collision");
	mLifeMax = GameConfig::getI("trader-life");
	mLife = mLifeMax;
	mArmorMax = GameConfig::getI("trader-armor");
	mArmor = mArmorMax;
	mSpeed = GameConfig::getF("trader-speed");
	mFactionCode = 1;

	mStock = 0;
	mStockMax = GameConfig::getU("trader-capacity");

	mWaiting = true;
}

void TradeShip::setDestination(const oe::Vector2& position)
{
	mDestination = position;
	oe::Vector2 delta = position - getPosition();
	F32 angle = delta.getPolarAngle();
	setRotation(angle + 90.0f);
	mDirection = oe::Vector2::polarVector(angle);

	stopWait();
}

bool TradeShip::destinationReached() const
{
	return mWaiting;
}

void TradeShip::update(oe::Time dt)
{
	if (GameConfig::getU("aabb") == 1)
	{
		oe::DebugDraw::drawRect(getCollision());
		oe::DebugDraw::drawRect(getAABB(), oe::Color::Green);
	}

	if (!mWaiting && mDestination.distance(getPosition()) < 20.0f)
	{
		mProp.setTextureRect(sf::IntRect(0, 0, 1, 1));
		mWaiting = true;
	}

	if (!mWaiting)
	{
		F32 stock = F32(mStockMax - mStock) / F32(mStockMax);
		F32 s = mSpeed + 200.0f * stock;
		move(mDirection * dt.asSeconds() * s);
	}

	// Armor
	if (hasArmor())
	{
		mShield.setTextureRect(sf::IntRect(320, 4, 148, 233));
	}
	else
	{
		mShield.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}
}

void TradeShip::stopWait()
{
	mProp.setTextureRect(sf::IntRect(109, 74, 103, 131));
	mWaiting = false;
}

void TradeShip::onDie()
{
	GameSingleton::mRestart = true;
}

void TradeShip::updateFromShop()
{
	mStockMax = GameSingleton::mTraderCapacity;
	mStock = GameSingleton::mResource1 + GameSingleton::mResource2 + GameSingleton::mResource3;
	mLifeMax = GameSingleton::mTraderLife;
	mArmorMax = GameSingleton::mTraderArmor;
}

void TradeShip::setStock(U32 stock)
{
	mStock = stock;
}

void TradeShip::setStockMax(U32 stockMax)
{
	mStockMax = stockMax;
}

U32 TradeShip::getStock() const
{
	return mStock;
}

U32 TradeShip::getStockMax() const
{
	return mStockMax;
}
