#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/ParticleComponent.hpp"

class Explosion : public oe::Entity
{
	public:
		Explosion(oe::EntityManager& manager, const oe::Vector2& position, U32 type);

		virtual void update(oe::Time dt);

	private:
		oe::ParticleComponent mParticles;
};

#endif // WRITINGTEXT_HPP
