#ifndef INDICATOR_HPP
#define INDICATOR_HPP

#include "../Engine/Core/World.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Indicator : public sf::Drawable, public sf::Transformable
{
	public:
		Indicator(oe::World& world, U32 type, const oe::EntityHandle& handle);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(const oe::Vector2& playerPosition);

		void setEntity(const oe::EntityHandle& handle);

		bool needToBeRemoved() const;

	private:
		oe::World& mWorld;
		oe::EntityHandle mHandle;
		sf::Sprite mSprite;
		bool mVisible; // Is the object visible, not the indicator
};

#endif // BAR_HPP
