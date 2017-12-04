#include "EnemyShip.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "Projectile.hpp"

#include "../Engine/Core/World.hpp"

Enemy1Ship::Enemy1Ship(oe::EntityManager& manager, const oe::Vector2& position)
	: Ship(manager, 3)
	, mLifeBar(*this)
	, mArmorBar(*this)
{
	setPosition(position);
	setPositionZ(3);

	mShip.setTexture(GameSingleton::mEnemy1Texture);
	mShip.setTextureRect(sf::IntRect(0, 0, 84, 87));
	mShip.setPosition(-42, -43);
	mShip.setPositionZ(0);

	mProp.setTexture(GameSingleton::mEnemy1Texture);
	mProp.setTextureRect(sf::IntRect(0, 0, 1, 1));
	mProp.setPosition(-42 + 37, -43 + 86);
	mProp.setPositionZ(1);

	mShield.setTexture(GameSingleton::mEnemy1Texture);
	mShield.setTextureRect(sf::IntRect(6, 111, 104, 98));
	mShield.setPosition(-52, -44);

	mCollisionSize = GameConfig::getF("enemy1-collision");
	mLifeMax = GameConfig::getI("enemy1-life");
	mLife = mLifeMax;
	mArmorMax = GameConfig::getI("enemy1-armor");
	mArmor = mArmorMax;
	mSpeed = GameConfig::getF("enemy1-speed");
	mFactionCode = 2;

	mLifeBar.setSize(40, 5);
	mLifeBar.setPosition(-20, -50);
	mLifeBar.setPositionZ(20);
	mLifeBar.setBackColor(sf::Color(172, 172, 172));
	mLifeBar.setBarColor(sf::Color::Green);
	mLifeBar.setOutlineColor(sf::Color(32, 32, 32));
	mLifeBar.setOutlineThickness(1.2f);
	mLifeBar.setValueMax(F32(mLifeMax));
	mLifeBar.setValue(F32(mLife));

	mArmorBar.setSize(40, 5);
	mArmorBar.setPosition(-20, -45);
	mArmorBar.setPositionZ(20);
	mArmorBar.setBackColor(sf::Color(172, 172, 172));
	mArmorBar.setBarColor(sf::Color::Cyan);
	mArmorBar.setOutlineColor(sf::Color(32, 32, 32));
	mArmorBar.setOutlineThickness(1.2f);
	mArmorBar.setValueMax(F32(mArmorMax));
	mArmorBar.setValue(F32(mArmor));
}

void Enemy1Ship::update(oe::Time dt)
{
	if (GameConfig::getU("aabb") == 1)
	{
		oe::DebugDraw::drawRect(getCollision());
		oe::DebugDraw::drawRect(getAABB(), oe::Color::Green);
	}

	// Bar
	mLifeBar.setValue(F32(mLife));
	mArmorBar.setValue(F32(mArmor));

	// Direction
	oe::Vector2 delta = GameSingleton::mPlayerShip->getPosition() - getPosition();
	F32 angle = delta.getPolarAngle();
	setRotation(angle + 90.0f);

	// Armor
	if (hasArmor())
	{
		mShield.setTextureRect(sf::IntRect(6, 111, 104, 98));
	}
	else
	{
		mShield.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}

	// Movement
	U32 index = 0;
	F32 distance = 9999.0f;
	if (!delta.isZero())
	{
		distance = delta.getLength();
		if (distance > GameConfig::getF("enemy-stop"))
		{
			index = 1;
			move((delta / distance) * dt.asSeconds() * mSpeed);
		}
	}

	// Prop
	if (index == 1)
	{
		mProp.setTextureRect(sf::IntRect(40, 97, 9, 6));
	}
	else
	{
		mProp.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}

	// Fire
	mCooldown += dt;
	if (!delta.isZero())
	{
		if (distance < GameConfig::getF("enemy-vision"))
		{
			fire();
		}
	}
}

void Enemy1Ship::fire()
{
	if (mCooldown > oe::seconds(GameConfig::getF("enemy-cooldown")))
	{
		mCooldown = oe::Time::Zero;

		oe::Vector2 delta = GameSingleton::mPlayerShip->getPosition() - getPosition();
		F32 angle = delta.getPolarAngle() + 90.0f;
		oe::Vector2 dir = oe::Vector2::polarVector(angle);

		oe::Vector2 p = mShip.getPosition();
		oe::Vector2 p1 = oe::Vector2(15, 2) + p;
		oe::Vector2 p2 = oe::Vector2(67, 2) + p;

		getManager().createEntity<Projectile>(3, p1.getRotated(angle) + getPosition(), dir);
		getManager().createEntity<Projectile>(3, p2.getRotated(angle) + getPosition(), dir);

		GameSingleton::playSound(GameSingleton::mShoot2Sound, getPosition());
	}
}










Enemy2Ship::Enemy2Ship(oe::EntityManager& manager, const oe::Vector2& position)
	: Ship(manager, 3)
	, mLifeBar(*this)
	, mArmorBar(*this)
{
	setPosition(position);
	setPositionZ(4);

	mShip.setTexture(GameSingleton::mEnemy2Texture);
	mShip.setTextureRect(sf::IntRect(0, 0, 135, 82));
	mShip.setPosition(-72, -41);
	mShip.setPositionZ(0);

	mProp.setTexture(GameSingleton::mEnemy2Texture);
	mProp.setTextureRect(sf::IntRect(0, 0, 1, 1));
	mProp.setPosition(-72 + 63, -41 + 81);
	mProp.setPositionZ(1);

	mShield.setTexture(GameSingleton::mEnemy2Texture);
	mShield.setTextureRect(sf::IntRect(0, 106, 139, 79));
	mShield.setPosition(-70, -40);

	mCollisionSize = GameConfig::getF("enemy2-collision");
	mLifeMax = GameConfig::getI("enemy2-life");
	mLife = mLifeMax;
	mArmorMax = GameConfig::getI("enemy2-armor");
	mArmor = mArmorMax;
	mSpeed = GameConfig::getF("enemy2-speed");
	mFactionCode = 2;

	mLifeBar.setSize(40, 5);
	mLifeBar.setPosition(-20, -50);
	mLifeBar.setPositionZ(20);
	mLifeBar.setBackColor(sf::Color(172, 172, 172));
	mLifeBar.setBarColor(sf::Color::Green);
	mLifeBar.setOutlineColor(sf::Color(32, 32, 32));
	mLifeBar.setOutlineThickness(1.2f);
	mLifeBar.setValueMax(F32(mLifeMax));
	mLifeBar.setValue(F32(mLife));

	mArmorBar.setSize(40, 5);
	mArmorBar.setPosition(-20, -45);
	mArmorBar.setPositionZ(20);
	mArmorBar.setBackColor(sf::Color(172, 172, 172));
	mArmorBar.setBarColor(sf::Color::Cyan);
	mArmorBar.setOutlineColor(sf::Color(32, 32, 32));
	mArmorBar.setOutlineThickness(1.2f);
	mArmorBar.setValueMax(F32(mArmorMax));
	mArmorBar.setValue(F32(mArmor));

	mFocusTrader = oe::Random::getBool();
}

void Enemy2Ship::update(oe::Time dt)
{
	if (GameConfig::getU("aabb") == 1)
	{
		oe::DebugDraw::drawRect(getCollision());
		oe::DebugDraw::drawRect(getAABB(), oe::Color::Green);
	}

	// Bar
	mLifeBar.setValue(F32(mLife));
	mArmorBar.setValue(F32(mArmor));

	// Direction
	oe::Vector2 delta = ((mFocusTrader) ? GameSingleton::mTradeShip->getPosition() : GameSingleton::mPlayerShip->getPosition()) - getPosition();
	F32 angle = delta.getPolarAngle();
	setRotation(angle + 90.0f);

	// Armor
	if (hasArmor())
	{
		mShield.setTextureRect(sf::IntRect(0, 106, 139, 79));
	}
	else
	{
		mShield.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}

	// Movement
	U32 index = 0;
	F32 distance = 9999.0f;
	if (!delta.isZero())
	{
		distance = delta.getLength();
		if (distance > GameConfig::getF("enemy-stop"))
		{
			index = 1;
			move((delta / distance) * dt.asSeconds() * mSpeed);
		}
	}

	// Prop
	if (index == 1)
	{
		mProp.setTextureRect(sf::IntRect(42, 88, 9, 6));
	}
	else
	{
		mProp.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}

	// Fire
	mCooldown += dt;
	if (!delta.isZero())
	{
		if (distance < GameConfig::getF("enemy-vision"))
		{
			fire();
		}
	}
}

void Enemy2Ship::fire()
{
	if (mCooldown > oe::seconds(GameConfig::getF("enemy-cooldown")))
	{
		mCooldown = oe::Time::Zero;

		oe::Vector2 delta = ((mFocusTrader) ? GameSingleton::mTradeShip->getPosition() : GameSingleton::mPlayerShip->getPosition()) - getPosition();
		F32 angle = delta.getPolarAngle() + 90.0f;
		oe::Vector2 dir = oe::Vector2::polarVector(angle);

		oe::Vector2 p = mShip.getPosition();
		oe::Vector2 p1 = oe::Vector2(35, 4) + p;
		oe::Vector2 p2 = oe::Vector2(99, 4) + p;

		getManager().createEntity<Projectile>(3, p1.getRotated(angle) + getPosition(), dir);
		getManager().createEntity<Projectile>(3, p2.getRotated(angle) + getPosition(), dir);

		GameSingleton::playSound(GameSingleton::mShoot2Sound, getPosition());

	}
}














Enemy3Ship::Enemy3Ship(oe::EntityManager& manager, const oe::Vector2& position)
	: Ship(manager, 3)
	, mLifeBar(*this)
	, mArmorBar(*this)
{
	setPosition(position);
	setPositionZ(-2);

	mShip.setTexture(GameSingleton::mEnemy3Texture);
	mShip.setTextureRect(sf::IntRect(0, 0, 160, 103));
	mShip.setPosition(-80, -51);
	mShip.setPositionZ(0);

	mProp.setTexture(GameSingleton::mEnemy3Texture);
	mProp.setTextureRect(sf::IntRect(0, 0, 1, 1));
	mProp.setPosition(-80 + 73, -51 + 80);
	mProp.setPositionZ(1);

	mShield.setTexture(GameSingleton::mEnemy3Texture);
	mShield.setTextureRect(sf::IntRect(2, 131, 184, 123));
	mShield.setPosition(-92, -61);

	mCollisionSize = GameConfig::getF("enemy3-collision");
	mLifeMax = GameConfig::getI("enemy3-life");
	mLife = mLifeMax;
	mArmorMax = GameConfig::getI("enemy3-armor");
	mArmor = mArmorMax;
	mSpeed = GameConfig::getF("enemy3-speed");
	mFactionCode = 2;

	mLifeBar.setSize(50, 5);
	mLifeBar.setPosition(-25, -50);
	mLifeBar.setPositionZ(20);
	mLifeBar.setBackColor(sf::Color(172, 172, 172));
	mLifeBar.setBarColor(sf::Color::Green);
	mLifeBar.setOutlineColor(sf::Color(32, 32, 32));
	mLifeBar.setOutlineThickness(1.2f);
	mLifeBar.setValueMax(F32(mLifeMax));
	mLifeBar.setValue(F32(mLife));

	mArmorBar.setSize(50, 5);
	mArmorBar.setPosition(-25, -45);
	mArmorBar.setPositionZ(20);
	mArmorBar.setBackColor(sf::Color(172, 172, 172));
	mArmorBar.setBarColor(sf::Color::Cyan);
	mArmorBar.setOutlineColor(sf::Color(32, 32, 32));
	mArmorBar.setOutlineThickness(1.2f);
	mArmorBar.setValueMax(F32(mArmorMax));
	mArmorBar.setValue(F32(mArmor));
}

void Enemy3Ship::update(oe::Time dt)
{
	if (GameConfig::getU("aabb") == 1)
	{
		oe::DebugDraw::drawRect(getCollision());
		oe::DebugDraw::drawRect(getAABB(), oe::Color::Green);
	}

	// Bar
	mLifeBar.setValue(F32(mLife));
	mArmorBar.setValue(F32(mArmor));

	// Direction
	oe::Vector2 delta = GameSingleton::mTradeShip->getPosition() - getPosition();
	F32 angle = delta.getPolarAngle();
	setRotation(angle + 90.0f);

	// Armor
	if (hasArmor())
	{
		mShield.setTextureRect(sf::IntRect(2, 131, 184, 123));
	}
	else
	{
		mShield.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}

	// Movement
	U32 index = 0;
	F32 distance = 9999.0f;
	if (!delta.isZero())
	{
		distance = delta.getLength();
		if (distance > GameConfig::getF("enemy-stop"))
		{
			index = 1;
			move((delta / distance) * dt.asSeconds() * mSpeed);
		}
	}

	// Prop
	if (index == 1)
	{
		mProp.setTextureRect(sf::IntRect(40, 109, 12, 8));
	}
	else
	{
		mProp.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}

	// Fire
	mCooldown += dt;
	if (!delta.isZero())
	{
		if (distance < GameConfig::getF("enemy-vision"))
		{
			fire();
		}
	}
}

void Enemy3Ship::fire()
{
	if (mCooldown > oe::seconds(GameConfig::getF("enemy-cooldown")))
	{
		mCooldown = oe::Time::Zero;

		oe::Vector2 delta = GameSingleton::mTradeShip->getPosition() - getPosition();
		F32 angle = delta.getPolarAngle() + 90.0f;
		oe::Vector2 dir = oe::Vector2::polarVector(angle);

		oe::Vector2 p = mShip.getPosition();
		oe::Vector2 p1 = oe::Vector2(34, 3) + p;
		oe::Vector2 p2 = oe::Vector2(123, 3) + p;

		getManager().createEntity<Projectile>(3, p1.getRotated(angle) + getPosition(), dir);
		getManager().createEntity<Projectile>(3, p2.getRotated(angle) + getPosition(), dir);

		GameSingleton::playSound(GameSingleton::mShoot2Sound, getPosition());
	}
}
