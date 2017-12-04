#include "Ship.hpp"

#include "GameSingleton.hpp"
#include "Explosion.hpp"
#include "../Engine/Core/EntityManager.hpp"

Ship::Ship(oe::EntityManager& manager, I32 type)
	: oe::Entity(manager)
	, mShip(*this)
	, mProp(*this)
	, mShield(*this)
{
	mType = type;
	mBoostMax = 0.0f;
	mBoost = 0.0f;
	mBoostRegen = 0.0f;
}

void Ship::update(oe::Time dt)
{
}

void Ship::onDie()
{
	kill();
	getManager().createEntity<Explosion>(getPosition(), 0);
	GameSingleton::playSound(GameSingleton::mExplosionSound, getPosition());
}

I32 Ship::getShipType() const
{
	return mType;
}

bool Ship::inflige(I32 damage)
{
	if (mArmor > 0)
	{
		mArmor -= damage;
		if (mArmor < 0)
		{
			mArmor = 0;

			GameSingleton::playSound(GameSingleton::mShieldSound, getPosition());
		}
	}
	else
	{
		bool wasAlive = isAlive();
		mLife -= damage;
		if (mLife < 0)
		{
			mLife = 0;
		}
		if (wasAlive && !isAlive())
		{
			return true;
		}
	}
	return false;
}

bool Ship::hasLifeMax() const
{
	return mLife >= mLifeMax;
}

bool Ship::hasArmorMax() const
{
	return mArmor >= mArmorMax;
}

void Ship::restoreLife(I32 amount)
{
	mLife += amount;
	if (mLife > mLifeMax)
	{
		mLife = mLifeMax;
	}
}

void Ship::restoreLifeMax()
{
	mLife = mLifeMax;
}

I32 Ship::getLife() const
{
	return mLife;
}

I32 Ship::getLifeMax() const
{
	return mLifeMax;
}

bool Ship::isAlive() const
{
	return mLife > 0;
}

void Ship::restoreArmorMax()
{
	mArmor = mArmorMax;
}

I32 Ship::getArmor() const
{
	return mArmor;
}

I32 Ship::getArmorMax() const
{
	return mArmorMax;
}

bool Ship::hasArmor() const
{
	return mArmor > 0;
}

F32 Ship::getSpeed() const
{
	return mSpeed;
}

I32 Ship::getFactionCode() const
{
	return mFactionCode;
}

void Ship::boostGain()
{
	if (mBoost < 0)
	{
		mBoostLow = true;
	}

	if (mBoost < mBoostMax)
	{
		mBoost += mBoostRegen;
	}
}

F32 Ship::getBoost() const
{
	return mBoost;
}

F32 Ship::getBoostMax() const
{
	return mBoostMax;
}

F32 Ship::getBoostRegen() const
{
	return mBoostRegen;
}

bool Ship::canUseBoost()
{
	if (mBoost > 150.0f && mBoostLow)
	{
		mBoostLow = false;
	}
	return mBoost > 0.0f && !mBoostLow;
}

bool Ship::isBoostLow() const
{
	return mBoostLow;
}

void Ship::fire()
{
}

oe::Rect Ship::getCollision() const
{
	oe::Vector2 p = getGlobalPosition() - oe::Vector2(mCollisionSize, mCollisionSize) * 0.5f;
	return oe::Rect(p.x, p.y, mCollisionSize, mCollisionSize);
}
