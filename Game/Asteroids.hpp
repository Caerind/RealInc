#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

class Asteroid : public oe::Entity
{
	public:
		Asteroid(oe::EntityManager& manager, const oe::Vector2& position);

		virtual void update(oe::Time dt);

		void inflige(I32 damage);
		void project(const oe::Vector2& position);

		bool canDamage() const;
		void resetCooldown();

		oe::Rect getCollision() const;

	protected:
		oe::SpriteComponent mAsteroid;
		oe::Time mCooldownDamage;
		I32 mLife;
		oe::Vector2 mDirection;
		F32 mCollisionSize;
		F32 mSpeed;
		F32 mRotSpeed;
		U32 mSkip;
};

class AsteroidChunk
{
	public:
		AsteroidChunk(oe::World& world);

		void init(U32 start, const oe::Vector2& pA);

		U32 getStarted() const;

		void remove();

	private:
		oe::World& mWorld;
		std::vector<oe::EntityHandle> mAsteroids;
		U32 mStarted;
};

#endif // WRITINGTEXT_HPP
