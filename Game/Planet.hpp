#ifndef PLANET_HPP
#define PLANET_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"
#include "../Engine/Core/EntityHandle.hpp"

class Planet : public oe::Entity
{
	public:
		Planet(oe::EntityManager& manager, const oe::Vector2& previousPlanetPos, U32 planetsReached);

		void update(oe::Time dt);

		F32 getScale() const;
		F32 getRadius() const;
		F32 getFinalRadius() const;
		const oe::Color& getColor() const;
		const std::string& getName() const;

		U32 getPrices(U32 index) const;
		U32 getDiscount() const;

		static F32 getLength(U32 reached);
		static oe::Color getRandomColor();
		static std::string getRandomName();

	private:
		oe::SpriteComponent mPlanet;
		F32 mScale;
		F32 mRadius;
		oe::Color mColor;
		std::string mName;

		U32 mPrices[6];
		U32 mDiscount;

};

#endif // WRITINGTEXT_HPP
