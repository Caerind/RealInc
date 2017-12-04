#include "PlayerShip.hpp"

#include "GameSingleton.hpp"

#include "GameConfig.hpp"

#include "Projectile.hpp"

#include "../Engine/Core/World.hpp"

PlayerShip::PlayerShip(oe::EntityManager& manager)
	: Ship(manager, 1)
{
	setPositionZ(2);

	mShip.setTexture(GameSingleton::mShipTexture);
	mShip.setTextureRect(sf::IntRect(0, 0, 182, 90));
	mShip.setPosition(-91, -45);

	mProp.setTexture(GameSingleton::mShipTexture);
	mProp.setTextureRect(sf::IntRect(83, 92, 15, 6));
	mProp.setPosition(-91 + 83, -45 + 77);
	mProp.setPositionZ(1);

	mShield.setTexture(GameSingleton::mShipTexture);
	mShield.setTextureRect(sf::IntRect(0, 115, 181, 89));
	mShield.setPosition(-90, -35);

	mCollisionSize = GameConfig::getF("player-collision");
	mLifeMax = GameConfig::getI("player-life");
	mLife = mLifeMax;
	mArmorMax = GameConfig::getI("player-armor");
	mArmor = mArmorMax;
	mSpeed = GameConfig::getF("player-speed");
	mFactionCode = 1;
	mBoostMax = GameConfig::getF("player-boost");
	mBoost = mBoostMax;
	mBoostRegen = GameConfig::getF("player-regen");
}

void PlayerShip::update(oe::Time dt)
{
	if (GameConfig::getU("aabb") == 1)
	{
		oe::DebugDraw::drawRect(getCollision());
		oe::DebugDraw::drawRect(getAABB(), oe::Color::Green);
	}

	// Direction
	oe::Vector2 deltaM = getApplication().getWindow().getCursorPositionView(getWorld().getRenderSystem().getView()) - getPosition();
	F32 angle = deltaM.getPolarAngle();
	setRotation(angle + 90.0f);

	// Armor
	if (hasArmor())
	{
		mShield.setTextureRect(sf::IntRect(0, 115, 181, 89));
	}
	else
	{
		mShield.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}

	// Movement
	oe::Vector2 mvt;
	bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	if (space && canUseBoost())
	{
		mProp.setTextureRect(sf::IntRect(83, 104, 15, 6));
		mvt = oe::Vector2::polarVector(angle, 3.0f);
		mBoost -= GameConfig::getF("boost-consume");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || space)
	{
		mProp.setTextureRect(sf::IntRect(83, 98, 15, 6));
		mvt = oe::Vector2::polarVector(angle);
		boostGain();
	}
	else
	{
		mProp.setTextureRect(sf::IntRect(83, 92, 15, 6));
		boostGain(); 
	}
	move(mvt * dt.asSeconds() * mSpeed);
	getWorld().getRenderSystem().getView().setCenter(getPosition());
}

void PlayerShip::fire()
{
	oe::Vector2 deltaM = getApplication().getWindow().getCursorPositionView(getWorld().getRenderSystem().getView()) - getPosition();
	F32 angle = deltaM.getPolarAngle() + 90.0f;
	oe::Vector2 dir = oe::Vector2::polarVector(angle);

	oe::Vector2 p = mShip.getPosition();
	oe::Vector2 p1 = oe::Vector2(61, 41) + p;
	oe::Vector2 p2 = oe::Vector2(113, 41) + p;

	getManager().createEntity<Projectile>(1, p1.getRotated(angle) + getPosition(), dir);
	getManager().createEntity<Projectile>(1, p2.getRotated(angle) + getPosition(), dir);

	GameSingleton::playSound(GameSingleton::mShoot1Sound, getPosition());
}

void PlayerShip::onDie()
{
	GameSingleton::mRestart = true;
}

void PlayerShip::updateFromShop()
{
	mLifeMax = GameSingleton::mPlayerLife;
	mArmorMax = GameSingleton::mPlayerArmor;
	mBoostMax = GameSingleton::mPlayerBoost;
}
