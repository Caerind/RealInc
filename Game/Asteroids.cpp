#include "Asteroids.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "Planet.hpp"

#include "Explosion.hpp"

#include "../Engine/Math/Random.hpp"
#include "../Engine/Core/EntityManager.hpp"
#include "../Engine/Core/World.hpp"

Asteroid::Asteroid(oe::EntityManager& manager, const oe::Vector2& position)
	: oe::Entity(manager)
	, mAsteroid(*this)
{
	setPosition(position);
	setPositionZ(0);
	setRotation(oe::Random::get<F32>(0.f, 360.f));

	U32 type = 0;
	if (oe::Random::get<U32>(0, 99) >= 80)
	{
		type = 1;
	}

	mDirection = oe::Vector2();

	if (type == 1)
	{
		mAsteroid.setTexture(GameSingleton::mAsteroidsLargeTexture);
		I32 x = oe::Random::get<I32>(0, 3);
		I32 y = oe::Random::get<I32>(0, 3);
		mAsteroid.setTextureRect(sf::IntRect(x * 320, y * 240, 320, 240));
		mAsteroid.setPosition(-160, -120);
		mCollisionSize = 200;
		mLife = GameConfig::getI("ast-life-1");
	}
	else
	{
		mAsteroid.setTexture(GameSingleton::mAsteroidsTexture);
		I32 x = oe::Random::get<I32>(0, 15);
		I32 y = oe::Random::get<I32>(0, 2);
		mAsteroid.setTextureRect(sf::IntRect(x * 120, y * 120, 120, 120));
		mAsteroid.setPosition(-60, -60);
		mCollisionSize = 120;
		mLife = GameConfig::getI("ast-life-0");
	}

	mCooldownDamage = oe::Time::Zero;

	mRotSpeed = 0.0f;

	mSkip = 1;
}

void Asteroid::update(oe::Time dt)
{
	if (GameConfig::getU("aabb") == 1)
	{
		oe::DebugDraw::drawRect(getCollision());
		oe::DebugDraw::drawRect(getAABB(), oe::Color::Green);
	}

	mSkip++;
	if (mSkip >= 2)
	{
		mSkip -= 2;
		dt *= 2.0f; 
		
		mCooldownDamage += dt;

		if (!mDirection.isZero() && !oe::Math::equals(mSpeed, 0.0f))
		{
			move(mDirection * dt.asSeconds() * mSpeed);
		}

		rotate(mRotSpeed * dt.asSeconds());

		const oe::Rect& r = getCollision();
		for (Entity* entity : GameSingleton::mEntityQuery.getEntities())
		{
			bool wasShip = false;
			Ship* ship = entity->getAs<Ship>();
			if (ship != nullptr && ship->getCollision().intersects(r) && canDamage())
			{
				wasShip = true;
				bool ret = ship->inflige(GameConfig::getI("ast-damage"));
				if (ret)
				{
					ship->onDie(); // ship die
				}
				inflige(GameConfig::getI("ast-damage"));
				project(ship->getPosition());

				resetCooldown();
			}
			if (!wasShip)
			{
				Asteroid* ast = entity->getAs<Asteroid>();
				if (ast != nullptr && ast->getId() != getId() && ast->getCollision().intersects(r) && canDamage())
				{
					ast->inflige(GameConfig::getI("ast-damage"));
					ast->project(getPosition());
					ast->resetCooldown();

					inflige(GameConfig::getI("ast-damage"));
					project(ast->getPosition());
					resetCooldown();
				}
			}
		}
	}
}

void Asteroid::inflige(I32 damage)
{
	mLife -= damage;
	if (mLife < 0)
	{
		kill();
		getManager().createEntity<Explosion>(getPosition(), 1);
		GameSingleton::playSound(GameSingleton::mAsteroidSound, getPosition());
	}
}

void Asteroid::project(const oe::Vector2& position)
{
	oe::Vector2 delta = getPosition() - position;
	if (!delta.isZero())
	{
		delta.normalize();
		if (mDirection.isZero() && oe::Math::equals(mSpeed, 0.0f))
		{
			mSpeed = 60.0f;
			mDirection = delta;
			mRotSpeed += oe::Random::getDev(0.0f, 10.0f);
		}
		else
		{
			if (mSpeed < 100.0f)
			{
				mSpeed *= 1.2f;
			}
			mDirection = (mDirection + delta) * 0.5f;
			mRotSpeed += oe::Random::getDev(0.0f, 10.0f);
		}
	}
}

bool Asteroid::canDamage() const
{
	return mCooldownDamage > oe::seconds(GameConfig::getF("ast-cooldown"));
}

void Asteroid::resetCooldown()
{
	mCooldownDamage = oe::Time::Zero;
}

oe::Rect Asteroid::getCollision() const
{
	oe::Vector2 p = getGlobalPosition() - oe::Vector2(mCollisionSize, mCollisionSize) * 0.5f;
	return oe::Rect(p.x, p.y, mCollisionSize, mCollisionSize);
}

AsteroidChunk::AsteroidChunk(oe::World& world)
	: mWorld(world)
{
	mStarted = 0;
}

void AsteroidChunk::init(U32 start, const oe::Vector2& pA)
{
	mStarted = start;

	U32 amount = GameConfig::getU("ast-amount");
	F32 length = Planet::getLength(start + 2);

	for (U32 i = 0; i < amount; i++)
	{
		F32 x = pA.x + oe::Random::get(300.0f, length - 300.0f);
		F32 y = pA.y + oe::Random::getDev(0.0f, length * 0.6f);

		mAsteroids.push_back(mWorld.getEntityManager().createEntity<Asteroid>(oe::Vector2(x, y)));
	}
}

U32 AsteroidChunk::getStarted() const
{
	return mStarted;
}

void AsteroidChunk::remove()
{
	for (U32 i = 0; i < mAsteroids.size(); i++)
	{
		mAsteroids[i].kill();
	}
}
