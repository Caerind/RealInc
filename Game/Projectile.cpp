#include "Projectile.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "Asteroids.hpp"

#include "../Engine/Math/Random.hpp"

Projectile::Projectile(oe::EntityManager& manager, I32 type, const oe::Vector2& position, const oe::Vector2& direction)
	: oe::Entity(manager)
	, mProj(*this)
{
	mType = type;

	setPosition(position);
	setPositionZ(10);
	setRotation(direction.getPolarAngle());

	mDirection = direction.getRotated(-90.0f);

	mProj.setTexture(GameSingleton::mProjTexture);
	mProj.setTextureRect(sf::IntRect(1 + (type-1) * 7, 1, 6, 13));
	mProj.setPosition(-3, -13);
}

void Projectile::update(oe::Time dt)
{
	if (GameConfig::getU("aabb") == 1)
	{
		oe::DebugDraw::drawRect(getAABB(), oe::Color::Green);
	}

	mDuration += dt;
	if (mDuration > oe::seconds(3.0f))
	{
		kill();
	}

	move(mDirection * dt.asSeconds() * GameConfig::getF("proj-speed"));


	const oe::Rect& r = getAABB();
	for (Entity* entity : GameSingleton::mEntityQuery.getEntities())
	{
		bool wasShip = false;
		Ship* ship = entity->getAs<Ship>();
		if (ship != nullptr && ship->getCollision().intersects(r))
		{
			wasShip = true;
			if ((mType == 3 && (ship->getFactionCode() == 1)) || ((mType == 2 || mType == 1) && ship->getFactionCode() == 2))
			{
				bool ret = ship->inflige(GameConfig::getI("proj-damage") + oe::Random::getDev<I32>(0, GameConfig::getI("proj-damagecrit")));

				if (ret)
				{
					ship->onDie(); // ship die
				}

				kill(); // Remove proj
			}
		}
		if (!wasShip)
		{
			Asteroid* ast = entity->getAs<Asteroid>();
			if (ast != nullptr && ast->getCollision().intersects(r))
			{
				ast->inflige(GameConfig::getI("proj-damage"));

				ast->project(getPosition());

				kill(); // Remove proj
			}
		}
	}
}

I32 Projectile::getProjType() const
{
	return mType;
}