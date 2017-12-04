#include "Explosion.hpp"

#include "../Engine/Core/World.hpp"

#include "GameSingleton.hpp"

Explosion::Explosion(oe::EntityManager& manager, const oe::Vector2& position, U32 type)
	: oe::Entity(manager)
	, mParticles(*this)
{
	setPosition(position);
	setPositionZ(6);

	mParticles.setTexture(GameSingleton::mParticleTexture);
	mParticles.addTextureRect(0, 0, 6, 6);

	switch (type)
	{
		case 0:
		{
			mParticles.setParticleVelocity(oe::Distributions::project(oe::Vector2(0.f, 1.f), 360.f, 50.f, 300.f));
			mParticles.setParticleScale(oe::Distributions::rect(oe::Vector2(1.5f, 1.5f), oe::Vector2(0.25f, 0.25f)));
			mParticles.setParticleLifetime(oe::Distributions::uniform(oe::seconds(0.4f), oe::seconds(0.5f)));
			mParticles.setParticleRotationSpeed(oe::Distributions::uniform(0.f, 180.f));
			mParticles.setParticleColor(oe::Distribution<oe::Color>([]() -> oe::Color
			{
				F32 g = oe::Random::get<F32>(30.f, 90.f);
				F32 r = (g - 10.f) * oe::Random::get<F32>(1.5f, 4.0f);
				if (r > 255.0f)
				{
					r = 255.0f;
				}
				return oe::Color((U8)r, (U8)g, 0);
			}));
			mParticles.emitParticles(100);
			break;

		} break;

		case 1:
		{
			mParticles.setParticleVelocity(oe::Distributions::project(oe::Vector2(0.f, 1.f), 360.f, 50.f, 300.f));
			mParticles.setParticleScale(oe::Distributions::rect(oe::Vector2(1.5f, 1.5f), oe::Vector2(0.25f, 0.25f)));
			mParticles.setParticleLifetime(oe::Distributions::uniform(oe::seconds(0.4f), oe::seconds(0.5f)));
			mParticles.setParticleRotationSpeed(oe::Distributions::uniform(0.f, 180.f));
			mParticles.setParticleColor(oe::Distribution<oe::Color>([]() -> oe::Color
			{
				F32 b = oe::Random::get(15.0f, 80.0f);
				F32 g = 2.0f * b;
				F32 r = 2.6f * b;
				return oe::Color((U8)r, (U8)g, (U8)b);
			}));
			mParticles.emitParticles(100);
			break;

		} break;
	}
}

void Explosion::update(oe::Time dt)
{
	if (mParticles.getParticleCount() == 0)
	{
		kill();
	}
}