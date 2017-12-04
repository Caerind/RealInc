#include "Indicator.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "GameSingleton.hpp"

Indicator::Indicator(oe::World& world, U32 type, const oe::EntityHandle& handle)
	: mWorld(world)
	, mHandle(handle)
{
	mSprite.setTexture(mWorld.getTextures().get(GameSingleton::mIndicatorTexture));
	mSprite.setTextureRect(sf::IntRect((type-1) * 32, 0, 32, 32));
	mSprite.setOrigin(16, 30);
	mSprite.setPosition(52, 111);

	// Is the object visible, not the indicator
	mVisible = true; // By default -> to not render the indicator
}

void Indicator::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!mVisible)
	{
		target.draw(mSprite);
	}
}

void Indicator::update(const oe::Vector2& playerPosition)
{
	if (mHandle.isValid())
	{
		oe::Rect aabb = mHandle->getAABB();
		if (aabb.intersects(mWorld.getRenderSystem().getView().getBounds()))
		{
			mVisible = true; // The obj is visible
		}
		else
		{
			mVisible = false; // The obj is outside the view
			
			// Prepare the indicator
			oe::Vector2 pObj = mHandle->getPosition();
			oe::Vector2 delta = pObj - playerPosition;
			F32 angle = delta.getPolarAngle();
			mSprite.setRotation(angle + 90.0f);
		}
	}
}

void Indicator::setEntity(const oe::EntityHandle& handle)
{
	mVisible = true;
	mHandle = handle;
}

bool Indicator::needToBeRemoved() const
{
	return !mHandle.isValid();
}
