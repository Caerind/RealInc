#include "TradeState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

TradeState::TradeState(oe::StateManager& manager, Planet* planet)
	: oe::State(manager)
	, mPlanet(planet)
{
	mRestorePlayerLife = false;
	mRestorePlayerArmor = false;
	mRestoreTraderLife = false;
	mRestoreTraderArmor = false;

	loadGUI();
	loadTexts();
	init();
}

bool TradeState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mPos = toSF(getApplication().getWindow().getCursorPosition());

		if (sf::FloatRect(0, 0, 180, 62).contains(mPos)) // Back
		{
			quit();
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(659, 180, 164, 58).contains(mPos) && !mRestorePlayerLife && GameSingleton::mMoney >= 20) // Restore life player
		{
			mRestorePlayerLife = true;
			GameSingleton::mMoney -= 20;
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(819, 180, 186, 58).contains(mPos) && !mRestorePlayerArmor && GameSingleton::mMoney >= 20) // Restore armor player
		{
			mRestorePlayerArmor = true;
			GameSingleton::mMoney -= 20;
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(659, 252, 164, 58).contains(mPos) && !mRestoreTraderLife && GameSingleton::mMoney >= 20) // Restore life trader
		{
			mRestoreTraderLife = true;
			GameSingleton::mMoney -= 20;
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(819, 252, 186, 58).contains(mPos) && !mRestoreTraderArmor && GameSingleton::mMoney >= 20) // Restore armor trader
		{
			mRestoreTraderArmor = true;
			GameSingleton::mMoney -= 20;
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(594, 495, 131, 51).contains(mPos) && GameSingleton::mMoney >= mPriceP1) // P1
		{
			GameSingleton::mMoney -= mPriceP1;
			GameSingleton::mBuyIndexes[0]++;
			mPriceP1 = priceP1();

			GameSingleton::mPlayerBoost += 250.0f; // TODO : Value

			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mPriceP1Text, oe::toString(mPriceP1));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(594, 568, 131, 51).contains(mPos) && GameSingleton::mMoney >= mPriceP2) // P2
		{
			GameSingleton::mMoney -= mPriceP2;
			GameSingleton::mBuyIndexes[1]++;
			mPriceP2 = priceP2();

			GameSingleton::mPlayerLife += 30; // TODO : Value

			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mPriceP2Text, oe::toString(mPriceP2));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(594, 641, 131, 51).contains(mPos) && GameSingleton::mMoney >= mPriceP3) // P3
		{
			GameSingleton::mMoney -= mPriceP3;
			GameSingleton::mBuyIndexes[2]++;
			mPriceP3 = priceP3();

			GameSingleton::mPlayerArmor += 30; // TODO : Value

			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mPriceP3Text, oe::toString(mPriceP3));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(875, 495, 131, 51).contains(mPos) && GameSingleton::mMoney >= mPriceT1) // T1
		{
			GameSingleton::mMoney -= mPriceT1;
			GameSingleton::mBuyIndexes[3]++;
			mPriceT1 = priceT1();

			GameSingleton::mTraderCapacity += 3; // TODO : Value

			updateCapacity();
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mPriceT1Text, oe::toString(mPriceT1));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(875, 568, 131, 51).contains(mPos) && GameSingleton::mMoney >= mPriceT2) // T2
		{
			GameSingleton::mMoney -= mPriceT2;
			GameSingleton::mBuyIndexes[4]++;
			mPriceT2 = priceT2();

			GameSingleton::mTraderLife += 20; // TODO : Value

			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mPriceT2Text, oe::toString(mPriceT2));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(875, 641, 131, 51).contains(mPos) && GameSingleton::mMoney >= mPriceT3) // T3
		{
			GameSingleton::mMoney -= mPriceT3;
			GameSingleton::mBuyIndexes[5]++;
			mPriceT3 = priceT3();

			GameSingleton::mTraderLife += 20; // TODO : Value

			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mPriceT3Text, oe::toString(mPriceT3));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(31, 280, 149, 49).contains(mPos) && GameSingleton::mMoney >= mPlanet->getPrices(0) && canBuyOne()) // B1
		{
			GameSingleton::mMoney -= mPlanet->getPrices(0);
			GameSingleton::mResource1++;
			updateCapacity();
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mQuantity1, oe::toString(GameSingleton::mResource1));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(31, 465, 149, 49).contains(mPos) && GameSingleton::mMoney >= mPlanet->getPrices(2) && canBuyOne()) // B2
		{
			GameSingleton::mMoney -= mPlanet->getPrices(2);
			GameSingleton::mResource2++;
			updateCapacity();
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mQuantity2, oe::toString(GameSingleton::mResource2));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(31, 673, 149, 49).contains(mPos) && GameSingleton::mMoney >= mPlanet->getPrices(4) && canBuyOne()) // B3
		{
			GameSingleton::mMoney -= mPlanet->getPrices(4);
			GameSingleton::mResource3++;
			updateCapacity();
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mQuantity3, oe::toString(GameSingleton::mResource3));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(223, 280, 149, 49).contains(mPos) && GameSingleton::mResource1 > 0) // S1
		{
			GameSingleton::mMoney += mPlanet->getPrices(1);
			GameSingleton::mResource1--;
			updateCapacity();
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mQuantity1, oe::toString(GameSingleton::mResource1));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(223, 465, 149, 49).contains(mPos) && GameSingleton::mResource2 > 0) // S2
		{
			GameSingleton::mMoney += mPlanet->getPrices(3);
			GameSingleton::mResource2--;
			updateCapacity();
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mQuantity2, oe::toString(GameSingleton::mResource2));
			GameSingleton::playClick();
		}
		else if (sf::FloatRect(223, 673, 149, 49).contains(mPos) && GameSingleton::mResource3 > 0) // S3
		{
			GameSingleton::mMoney += mPlanet->getPrices(5);
			GameSingleton::mResource3--;
			updateCapacity();
			setText(mMoneyText, oe::toString(GameSingleton::mMoney));
			setText(mQuantity3, oe::toString(GameSingleton::mResource3));
			GameSingleton::playClick();
		}
	}
	return false;
}

bool TradeState::update(oe::Time dt)
{
	if (GameSingleton::mMoney < 20 || mRestorePlayerLife)
		mRLP.setPosition(659, 180);
	else
		mRLP.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < 20 || mRestorePlayerArmor)
		mRAP.setPosition(819, 180);
	else
		mRAP.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < 20 || mRestoreTraderLife)
		mRLT.setPosition(659, 252);
	else
		mRLT.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < 20 || mRestoreTraderArmor)
		mRAT.setPosition(819, 252);
	else
		mRAT.setPosition(-1000, -1000);

	if (GameSingleton::mMoney < mPriceP1)
		mPriceP1Sprite.setPosition(594, 495);
	else
		mPriceP1Sprite.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < mPriceP2)
		mPriceP2Sprite.setPosition(594, 568);
	else
		mPriceP2Sprite.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < mPriceP3)
		mPriceP3Sprite.setPosition(594, 641);
	else
		mPriceP3Sprite.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < mPriceT1)
		mPriceT1Sprite.setPosition(875, 495);
	else
		mPriceT1Sprite.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < mPriceT2)
		mPriceT2Sprite.setPosition(875, 568);
	else
		mPriceT2Sprite.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < mPriceT3)
		mPriceT3Sprite.setPosition(875, 641);
	else
		mPriceT3Sprite.setPosition(-1000, -1000);

	if (GameSingleton::mMoney < mPlanet->getPrices(0) || !canBuyOne())
		mR1BSprite.setPosition(31, 280);
	else
		mR1BSprite.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < mPlanet->getPrices(2) || !canBuyOne())
		mR2BSprite.setPosition(31, 465);
	else
		mR2BSprite.setPosition(-1000, -1000);
	if (GameSingleton::mMoney < mPlanet->getPrices(4) || !canBuyOne())
		mR3BSprite.setPosition(31, 673);
	else
		mR3BSprite.setPosition(-1000, -1000);

	if (GameSingleton::mResource1 <= 0)
		mR1SSprite.setPosition(223, 280);
	else
		mR1SSprite.setPosition(-1000, -1000);
	if(GameSingleton::mResource2 <= 0)
		mR2SSprite.setPosition(223, 465);
	else
		mR2SSprite.setPosition(-1000, -1000);
	if (GameSingleton::mResource3 <= 0)
		mR3SSprite.setPosition(223, 673);
	else
		mR3SSprite.setPosition(-1000, -1000);

	return false;
}

void TradeState::render(sf::RenderTarget & target)
{
	target.draw(mBack);

	target.draw(mPlanetText);
	target.draw(mMoneyText);
	target.draw(mQuantity1);
	target.draw(mQuantity2);
	target.draw(mQuantity3);

	target.draw(mRLP);
	target.draw(mRAP);
	target.draw(mRLT);
	target.draw(mRAT);

	target.draw(mPriceP1Sprite);
	target.draw(mPriceP2Sprite);
	target.draw(mPriceP3Sprite);
	target.draw(mPriceT1Sprite);
	target.draw(mPriceT2Sprite);
	target.draw(mPriceT3Sprite);
	target.draw(mPriceP1Text);
	target.draw(mPriceP2Text);
	target.draw(mPriceP3Text);
	target.draw(mPriceT1Text);
	target.draw(mPriceT2Text);
	target.draw(mPriceT3Text);

	target.draw(mR1BSprite);
	target.draw(mR2BSprite);
	target.draw(mR3BSprite);
	target.draw(mR1SSprite);
	target.draw(mR2SSprite);
	target.draw(mR3SSprite);
	target.draw(mR1BText);
	target.draw(mR2BText);
	target.draw(mR3BText);
	target.draw(mR1SText);
	target.draw(mR2SText);
	target.draw(mR3SText);

	target.draw(mCapacityBar);
	target.draw(mCapacityText);

	target.draw(mDiscountSprite);
}

inline oe::Window & TradeState::getWindow()
{
	return getApplication().getWindow();
}

void TradeState::loadGUI()
{
	sf::Texture& texture = getApplication().getTextures().get(GameSingleton::mUITopTexture);

	#define CONFBUTTON(button, xb, yb, wb, hb) \
		button.setTexture(texture); \
		button.setTextureRect(sf::IntRect(xb, yb, wb, hb)); \
		button.setPosition(-1000, -1000);

	CONFBUTTON(mRLP, 659, 180, 164, 58);
	CONFBUTTON(mRAP, 819, 180, 186, 58);
	CONFBUTTON(mRLT, 659, 252, 164, 58);
	CONFBUTTON(mRAT, 819, 252, 186, 58);
	CONFBUTTON(mPriceP1Sprite, 594, 495, 131, 51);
	CONFBUTTON(mPriceP2Sprite, 594, 568, 131, 51);
	CONFBUTTON(mPriceP3Sprite, 594, 641, 131, 51);
	CONFBUTTON(mPriceT1Sprite, 875, 495, 131, 51);
	CONFBUTTON(mPriceT2Sprite, 875, 568, 131, 51);
	CONFBUTTON(mPriceT3Sprite, 875, 641, 131, 51);
	CONFBUTTON(mR1BSprite, 31, 280, 149, 49);
	CONFBUTTON(mR2BSprite, 31, 465, 149, 49);
	CONFBUTTON(mR3BSprite, 31, 673, 149, 49);
	CONFBUTTON(mR1SSprite, 223, 280, 149, 49);
	CONFBUTTON(mR2SSprite, 223, 465, 149, 49);
	CONFBUTTON(mR3SSprite, 223, 673, 149, 49);

	if (mPlanet->getDiscount() == 0)
	{
		CONFBUTTON(mDiscountSprite, 390, 280, 100, 50);
		mDiscountSprite.setPosition(390, 280);
	}
	else if (mPlanet->getDiscount() == 1)
	{
		CONFBUTTON(mDiscountSprite, 390, 465, 100, 50);
		mDiscountSprite.setPosition(390, 465);
	}
	else if (mPlanet->getDiscount() == 2)
	{
		CONFBUTTON(mDiscountSprite, 390, 673, 100, 50);
		mDiscountSprite.setPosition(390, 673);
	}

	#undef CONFTEXT

	mBack.setTexture(getApplication().getTextures().get(GameSingleton::mUIBackTexture));

	mCapacityBar.setBarColor(sf::Color::Yellow);
	mCapacityBar.setBackColor(sf::Color(127, 127, 127));
	mCapacityBar.setOutlineColor(sf::Color(192, 192, 192));
	mCapacityBar.setOutlineThickness(3.0f);
	mCapacityBar.setPosition(180, 142);
	mCapacityBar.setSize(270, 35);
}

void TradeState::loadTexts()
{
	sf::Font& font = getApplication().getFonts().get(GameSingleton::mFont);

	#define CONFTEXT(text) \
		text.setFont(font); \
		text.setFillColor(sf::Color::Black); \
		text.setCharacterSize(30);

	CONFTEXT(mPlanetText);
	CONFTEXT(mMoneyText);
	CONFTEXT(mQuantity1);
	CONFTEXT(mQuantity2);
	CONFTEXT(mQuantity3);
	CONFTEXT(mPriceP1Text);
	CONFTEXT(mPriceP2Text);
	CONFTEXT(mPriceP3Text);
	CONFTEXT(mPriceT1Text);
	CONFTEXT(mPriceT2Text);
	CONFTEXT(mPriceT3Text);
	CONFTEXT(mR1BText);
	CONFTEXT(mR2BText);
	CONFTEXT(mR3BText);
	CONFTEXT(mR1SText);
	CONFTEXT(mR2SText);
	CONFTEXT(mR3SText);
	CONFTEXT(mCapacityText);

	#undef CONFTEXT

	mPlanetText.setPosition(426, 37);
	mMoneyText.setPosition(945, 28);
	mQuantity1.setPosition(310, 234);
	mQuantity2.setPosition(310, 419);
	mQuantity3.setPosition(310, 628);
	mPriceP1Text.setPosition(656, 522);
	mPriceP2Text.setPosition(656, 595);
	mPriceP3Text.setPosition(656, 668);
	mPriceT1Text.setPosition(940, 522);
	mPriceT2Text.setPosition(940, 595);
	mPriceT3Text.setPosition(940, 668);
	mR1BText.setPosition(136, 306);
	mR2BText.setPosition(136, 490);
	mR3BText.setPosition(136, 699);
	mR1SText.setPosition(324, 306);
	mR2SText.setPosition(324, 493);
	mR3SText.setPosition(324, 699);
	mCapacityText.setPosition(314, 164);
}

void TradeState::init()
{
	if (GameSingleton::mPlayerShip->hasLifeMax())
	{
		mRestorePlayerLife = true;
		mRLP.setPosition(659, 180);
	}
	if (GameSingleton::mPlayerShip->hasArmorMax())
	{
		mRestorePlayerArmor = true;
		mRAP.setPosition(819, 180);
	}
	if (GameSingleton::mTradeShip->hasLifeMax())
	{
		mRestoreTraderLife = true;
		mRLT.setPosition(659, 252);
	}
	if (GameSingleton::mTradeShip->hasArmorMax())
	{
		mRestoreTraderArmor = true;
		mRAT.setPosition(819, 252);
	}

	mPriceP1 = priceP1();
	mPriceP2 = priceP2();
	mPriceP3 = priceP3();
	mPriceT1 = priceT1();
	mPriceT2 = priceT2();
	mPriceT3 = priceT3();

	setText(mPriceP1Text, oe::toString(mPriceP1));
	setText(mPriceP2Text, oe::toString(mPriceP2));
	setText(mPriceP3Text, oe::toString(mPriceP3));
	setText(mPriceT1Text, oe::toString(mPriceT1));
	setText(mPriceT2Text, oe::toString(mPriceT2));
	setText(mPriceT3Text, oe::toString(mPriceT3));

	mPlanetText.setCharacterSize(40);
	setText(mPlanetText, mPlanet->getName());

	setText(mMoneyText, oe::toString(GameSingleton::mMoney));

	setText(mQuantity1, oe::toString(GameSingleton::mResource1));
	setText(mQuantity2, oe::toString(GameSingleton::mResource2));
	setText(mQuantity3, oe::toString(GameSingleton::mResource3));

	setText(mR1BText, oe::toString(mPlanet->getPrices(0)));
	setText(mR2BText, oe::toString(mPlanet->getPrices(2)));
	setText(mR3BText, oe::toString(mPlanet->getPrices(4)));
	setText(mR1SText, oe::toString(mPlanet->getPrices(1)));
	setText(mR2SText, oe::toString(mPlanet->getPrices(3)));
	setText(mR3SText, oe::toString(mPlanet->getPrices(5)));

	updateCapacity();
}

void TradeState::quit()
{
	GameSingleton::mIsOnTrade = false;

	GameSingleton::mPlayerShip->updateFromShop();
	GameSingleton::mTradeShip->updateFromShop();

	if (mRestorePlayerLife)
	{
		GameSingleton::mPlayerShip->restoreLifeMax();
	}
	if (mRestorePlayerArmor)
	{
		GameSingleton::mPlayerShip->restoreArmorMax();
	}

	if (mRestoreTraderLife)
	{
		GameSingleton::mTradeShip->restoreLifeMax();
	}
	if (mRestoreTraderArmor)
	{
		GameSingleton::mTradeShip->restoreArmorMax();
	}

	popState();
}

U32 TradeState::priceP1()
{
	return GameSingleton::mBuyIndexes[0] * (10 + GameSingleton::mBuyIndexes[0]) + 20;
}

U32 TradeState::priceP2()
{
	return GameSingleton::mBuyIndexes[1] * (10 + GameSingleton::mBuyIndexes[1]) + 20;
}

U32 TradeState::priceP3()
{
	return GameSingleton::mBuyIndexes[2] * (10 + GameSingleton::mBuyIndexes[2]) + 20;
}

U32 TradeState::priceT1()
{
	return GameSingleton::mBuyIndexes[3] * (10 + GameSingleton::mBuyIndexes[3]) + 20;
}

U32 TradeState::priceT2()
{
	return GameSingleton::mBuyIndexes[4] * (10 + GameSingleton::mBuyIndexes[4]) + 20;
}

U32 TradeState::priceT3()
{
	return GameSingleton::mBuyIndexes[5] * (10 + GameSingleton::mBuyIndexes[5]) + 20;
}

U32 TradeState::quantity() const
{
	return GameSingleton::mResource1 + GameSingleton::mResource2 + GameSingleton::mResource3;
}

bool TradeState::canBuyOne() const
{
	return quantity() < GameSingleton::mTraderCapacity;
}

void TradeState::updateCapacity()
{
	setText(mCapacityText, oe::toString(quantity()) + " / " + oe::toString(GameSingleton::mTraderCapacity));
	mCapacityBar.setValueMax(F32(GameSingleton::mTraderCapacity));
	mCapacityBar.setValue(F32(quantity()));
}

void TradeState::setText(sf::Text & text, const std::string& str)
{
	text.setString(str);
	text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height);
}
