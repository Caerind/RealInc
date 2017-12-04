#ifndef PLAYERSHIP_HPP
#define PLAYERSHIP_HPP

#include "Ship.hpp"

class PlayerShip : public Ship
{
	public:
		PlayerShip(oe::EntityManager& manager);

		virtual void update(oe::Time dt);

		virtual void fire();

		virtual void onDie();

		void updateFromShop();

	private:

};

#endif // WRITINGTEXT_HPP
