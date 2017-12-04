#ifndef ENEMYSHIP_HPP
#define ENEMYSHIP_HPP

#include "Ship.hpp"

#include "BarComponent.hpp"

class Enemy1Ship : public Ship
{
	public:
		Enemy1Ship(oe::EntityManager& manager, const oe::Vector2& position);

		virtual void update(oe::Time dt);

		virtual void fire();

	private:
		BarComponent mLifeBar;
		BarComponent mArmorBar;
		oe::Time mCooldown;
};

class Enemy2Ship : public Ship
{
	public:
		Enemy2Ship(oe::EntityManager& manager, const oe::Vector2& position);

		virtual void update(oe::Time dt);

		virtual void fire();

	private:
		BarComponent mLifeBar;
		BarComponent mArmorBar;
		oe::Time mCooldown;
		bool mFocusTrader;
};

class Enemy3Ship : public Ship
{
	public:
		Enemy3Ship(oe::EntityManager& manager, const oe::Vector2& position);

		virtual void update(oe::Time dt);

		virtual void fire();

	private:
		BarComponent mLifeBar;
		BarComponent mArmorBar;
		oe::Time mCooldown;
};

#endif // WRITINGTEXT_HPP
