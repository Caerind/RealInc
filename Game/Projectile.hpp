#ifndef PROJ_HPP
#define PROJ_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

class Projectile : public oe::Entity
{
	public:
		Projectile(oe::EntityManager& manager, I32 type, const oe::Vector2& position, const oe::Vector2& direction);

		virtual void update(oe::Time dt);

		I32 getProjType() const;

	protected:
		oe::SpriteComponent mProj;
	
		oe::Time mDuration;
		oe::Vector2 mDirection;
		I32 mType;
};

#endif // WRITINGTEXT_HPP
