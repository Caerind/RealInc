#ifndef SPACEMAP_HPP
#define SPACEMAP_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

class SpaceMap : public oe::Entity
{
	public:
		SpaceMap(oe::EntityManager& manager);
		~SpaceMap();

		virtual void update(oe::Time dt);

	private:
		std::vector<oe::SpriteComponent*> mTiles;
		oe::Vector2i mLastCoords;
};

#endif // SPACEMAP_HPP
