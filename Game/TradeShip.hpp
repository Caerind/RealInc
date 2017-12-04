#ifndef TRADESHIP_HPP
#define TRADESHIP_HPP

#include "Ship.hpp"

class TradeShip : public Ship
{
	public:
		TradeShip(oe::EntityManager& manager);

		void setDestination(const oe::Vector2& position);
		bool destinationReached() const;

		virtual void update(oe::Time dt);

		void stopWait();

		virtual void onDie();

		void updateFromShop();

		void setStock(U32 stock);
		void setStockMax(U32 stockMax);
		U32 getStock() const;
		U32 getStockMax() const;

	private:
		oe::Vector2 mDestination;
		oe::Vector2 mDirection;
		bool mWaiting;

		U32 mStock;
		U32 mStockMax;
};

#endif // WRITINGTEXT_HPP
