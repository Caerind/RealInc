#ifndef TRADESTATE_HPP
#define TRADESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/World.hpp"

#include "GameConfig.hpp"

#include "Bar.hpp"

#include "Planet.hpp"
#include "PlayerShip.hpp"
#include "TradeShip.hpp"

class TradeState : public oe::State
{
	public:
		TradeState(oe::StateManager& manager, Planet* planet);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

	private:
		inline oe::Window& getWindow();

		void loadGUI();
		void loadTexts();
		void init();

		void quit();

		U32 priceP1();
		U32 priceP2();
		U32 priceP3();
		U32 priceT1();
		U32 priceT2();
		U32 priceT3();

		U32 quantity() const;
		bool canBuyOne() const;
		void updateCapacity();

		static void setText(sf::Text& text, const std::string& str);

	private:
		Planet* mPlanet;
		bool mRestorePlayerLife;
		bool mRestorePlayerArmor;
		bool mRestoreTraderLife;
		bool mRestoreTraderArmor;

		sf::Sprite mBack;
		sf::Sprite mRLP;
		sf::Sprite mRAP;
		sf::Sprite mRLT;
		sf::Sprite mRAT;

		sf::Text mPlanetText;
		sf::Text mMoneyText;
		sf::Text mQuantity1;
		sf::Text mQuantity2;
		sf::Text mQuantity3;
		sf::Text mPriceP1Text;
		sf::Text mPriceP2Text;
		sf::Text mPriceP3Text;
		sf::Text mPriceT1Text;
		sf::Text mPriceT2Text;
		sf::Text mPriceT3Text;
		U32 mPriceP1;
		U32 mPriceP2;
		U32 mPriceP3;
		U32 mPriceT1;
		U32 mPriceT2;
		U32 mPriceT3;
		sf::Sprite mPriceP1Sprite;
		sf::Sprite mPriceP2Sprite;
		sf::Sprite mPriceP3Sprite;
		sf::Sprite mPriceT1Sprite;
		sf::Sprite mPriceT2Sprite;
		sf::Sprite mPriceT3Sprite;
		sf::Text mR1BText;
		sf::Text mR1SText;
		sf::Text mR2BText;
		sf::Text mR2SText;
		sf::Text mR3BText;
		sf::Text mR3SText;
		sf::Sprite mR1BSprite;
		sf::Sprite mR1SSprite;
		sf::Sprite mR2BSprite;
		sf::Sprite mR2SSprite;
		sf::Sprite mR3BSprite;
		sf::Sprite mR3SSprite;

		Bar mCapacityBar;
		sf::Text mCapacityText;

		sf::Sprite mDiscountSprite;
};

#endif // GAMESTATE_HPP
