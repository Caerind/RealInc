#ifndef SHIP_HPP
#define SHIP_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

class Ship : public oe::Entity
{
	public:
		Ship(oe::EntityManager& manager, I32 type);

		virtual void update(oe::Time dt);

		virtual void onDie();

		I32 getShipType() const;

		bool inflige(I32 damage);

		bool hasLifeMax() const;
		bool hasArmorMax() const;

		void restoreLife(I32 amount);
		void restoreLifeMax();
		I32 getLife() const;
		I32 getLifeMax() const;
		bool isAlive() const;

		void restoreArmorMax();
		I32 getArmor() const;
		I32 getArmorMax() const;
		bool hasArmor() const;

		F32 getSpeed() const;

		I32 getFactionCode() const;

		void boostGain();
		F32 getBoost() const;
		F32 getBoostMax() const;
		F32 getBoostRegen() const;
		bool canUseBoost();
		bool isBoostLow() const;

		virtual void fire();

		oe::Rect getCollision() const;

	protected:
		oe::SpriteComponent mShip;
		oe::SpriteComponent mProp;
		oe::SpriteComponent mShield;

		F32 mCollisionSize;
		
		I32 mType;
		I32 mLife;
		I32 mLifeMax;
		I32 mArmor;
		I32 mArmorMax;
		F32 mSpeed;
		I32 mFactionCode;
		F32 mBoost;
		F32 mBoostMax;
		F32 mBoostRegen;
		bool mBoostLow;
};

#endif // WRITINGTEXT_HPP
