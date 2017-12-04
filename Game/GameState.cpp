#include "GameState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"
#include "MenuState.hpp"

#include "../Engine/System/ParserXml.hpp"

GameState::GameState(oe::StateManager& manager)
	: oe::State(manager)
	, mWorld(manager.getApplication())
{
	GameSingleton::clear();

	// View settings
	getView().setCenter(0.0f, 0.0f);
	getView().setSize(getApplication().getWindow().getSize());
	getView().setZoom(2.0f);

	// Query
	mWorld.getEntityManager().addQuery(&GameSingleton::mEntityQuery);

	// Space
	mWorld.getEntityManager().createEntity<SpaceMap>();

	// Level begin
	mPlanetsReached = 0;
	mIsOnPlanet = false;
	mSpawnerLimit = oe::Time::Zero;
	mPlanetCurrent.invalidate(); 
	mPlanetDestination = mWorld.getEntityManager().createEntity<Planet>(oe::Vector2(), 0);
	mPlanetFuture = mWorld.getEntityManager().createEntity<Planet>(mPlanetDestination->getPosition(), 1);

	GameSingleton::mPlayerHandle = mWorld.getEntityManager().createEntity<PlayerShip>();
	GameSingleton::mPlayerShip = GameSingleton::mPlayerHandle.getAs<PlayerShip>();
	GameSingleton::mTradeHandle = mWorld.getEntityManager().createEntity<TradeShip>();
	GameSingleton::mTradeShip = GameSingleton::mTradeHandle.getAs<TradeShip>();
	GameSingleton::mPlayerShip->setPosition(mPlanetDestination->getPosition() + oe::Vector2(300, 300));
	GameSingleton::mTradeShip->setPosition(mPlanetDestination->getPosition());

	// 2 defaults indicators
	mIndicators.emplace_back(mWorld, 1, GameSingleton::mTradeHandle);
	mIndicators.emplace_back(mWorld, 2, mPlanetDestination);

	// Load GUI
	loadGUI();

	mWorld.play();
}

bool GameState::handleEvent(const sf::Event& event)
{
	OE_PROFILE_FUNCTION("GameState::handleEvent");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		devEvent(event);
	}

	bool clickHandled = false;

	sf::Vector2f mPos = toSF(getApplication().getWindow().getCursorPosition());

	if (mIsOnPlanet)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (sf::FloatRect(mPlanetPanel.getPosition().x + 11 * 0.8f, mPlanetPanel.getPosition().y + 214 * 0.8f - 182 * 0.8f, 171 * 0.8f, 88 * 0.8f).contains(mPos))
			{
				GameSingleton::mIsOnTrade = true;
				pushState<TradeState>(mPlanetDestination.getAs<Planet>());
				GameSingleton::playClick();
				clickHandled = true;
			}
			else if (sf::FloatRect(mPlanetPanel.getPosition().x + 11 * 0.8f, mPlanetPanel.getPosition().y + 372 * 0.8f - 182 * 0.8f, 171 * 0.8f, 88 * 0.8f).contains(mPos) && !clickHandled)
			{
				GameSingleton::playClick();
				mIsOnPlanet = false;
				leavePlanet();
				clickHandled = true;
			}
		}
	}

	if (!clickHandled && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && sf::FloatRect(mRightSprite.getPosition().x + 220 - 180, 13, 133, 93).contains(mPos))
	{
		GameSingleton::playClick();

		popState();
		pushState<MenuState>();

		clickHandled = true;
	}

	if (!clickHandled && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && GameSingleton::mPlayerHandle.isValid() && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && GameSingleton::mPlayerShip->canUseBoost()))
	{
		GameSingleton::mPlayerShip->fire();
	}

	return false;
}

bool GameState::update(oe::Time dt)
{
	OE_PROFILE_FUNCTION("GameState::update");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		dt *= 5.0f;
	}

	if (mIsOnPlanet)
	{
		mSpawnerLimit += dt;
		if (mSpawnerLimit > oe::seconds(GameConfig::getF("spawner-cooldown")))
		{
			mSpawnerLimit = oe::Time::Zero;
			spawnEnemy(1, 0, GameSingleton::mPlayerShip->getPosition() + oe::Vector2::polarVector(oe::Random::get<F32>(0, 360), GameConfig::getF("spawner-len")));
		}
	}

	mDuration += dt;

	mWorld.update(dt);

	if (GameSingleton::mRestart)
	{
		pushState<PopUp>();

		clearEnemies();

		mIsOnPlanet = false;

		if (mPlanetCurrent.isValid())
		{
			GameSingleton::mTradeShip->setPosition(mPlanetCurrent->getPosition());
		}
		else
		{
			GameSingleton::mTradeShip->setPosition(oe::Vector2(0, 0));
		}

		GameSingleton::mPlayerShip->setPosition(GameSingleton::mTradeShip->getPosition() + oe::Vector2(300, 300));

		GameSingleton::mTradeShip->stopWait();

		GameSingleton::mTradeShip->restoreLifeMax();
		GameSingleton::mTradeShip->restoreArmorMax();
		GameSingleton::mPlayerShip->restoreLifeMax();

		GameSingleton::mRestart = false;

		if (mPlanetsReached > 0)
		{
			generateEvent();
		}
	}

	// Update planets
	if (GameSingleton::mTradeHandle.isValid())
	{
		if (GameSingleton::mTradeShip->destinationReached() && !mIsOnPlanet)
		{
			mIsOnPlanet = true;
			mSpawnerLimit = oe::Time::Zero;
		}
	}

	// Update indicators
	for (U32 i = 0; i < mIndicators.size(); i++)
	{
		mIndicators[i].update(GameSingleton::mPlayerShip->getPosition());
	}

	// Update HUD
	mBoostBar.setValue(F32(GameSingleton::mPlayerShip->getBoost()));
	mLifeBar.setValue(F32(GameSingleton::mPlayerShip->getLife()));
	mArmorBar.setValue(F32(GameSingleton::mPlayerShip->getArmor()));
	mLifeBarTrader.setValue(F32(GameSingleton::mTradeShip->getLife()));
	mArmorBarTrader.setValue(F32(GameSingleton::mTradeShip->getArmor()));
	mTextPlanets.setString(oe::toString(mPlanetsReached));
	mTextPlanets.setOrigin(mTextPlanets.getGlobalBounds().width * 0.5f, mTextPlanets.getGlobalBounds().height);

	mProfiler.draw();
	mConfig.draw();

	return false;
}

void GameState::render(sf::RenderTarget& target)
{
	OE_PROFILE_FUNCTION("GameState::render");

	if (!GameSingleton::mIsOnTrade)
	{
		mWorld.render(target);

		target.draw(mBoostBar);
		target.draw(mLifeBar);
		target.draw(mArmorBar);
		target.draw(mLifeBarTrader);
		target.draw(mArmorBarTrader);
		target.draw(mLeftSprite);
		target.draw(mRightSprite);
		target.draw(mTextPlanets);
		for (U32 i = 0; i < mIndicators.size(); i++)
		{
			target.draw(mIndicators[i]);
		}
		if (mIsOnPlanet)
		{
			target.draw(mPlanetPanel);
		}
	}
}

oe::Window& GameState::getWindow()
{
	return getApplication().getWindow();
}

oe::View& GameState::getView()
{
	return mWorld.getRenderSystem().getView();
}

void GameState::devEvent(const sf::Event& event)
{
	// Screenshot
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
	{
		getWindow().screenshot();
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
	{
		if (mProfiler.isVisible())
		{
			mProfiler.hide();
		}
		else
		{
			mProfiler.show();
		}
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
	{
		if (mConfig.isVisible())
		{
			mConfig.hide();
		}
		else
		{
			mConfig.show();
		}
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F4)
	{
		if (mWorld.isPlaying())
		{
			mWorld.pause();
		}
		else
		{
			mWorld.play();
		}
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
	{
		static bool zoomed = true;
		if (zoomed)
		{
			getView().setZoom(10.f);
		}
		else
		{
			getView().setZoom(2.0f);
		}
		zoomed = !zoomed;
	}

}

void GameState::leavePlanet()
{
	mPlanetsReached++;
	GameSingleton::mMoney += 50;
	if (mPlanetCurrent.isValid())
	{
		mOldPlanets.push(mPlanetCurrent);
	}
	if (mPlanetDestination.isValid())
	{
		mPlanetCurrent = mPlanetDestination;
	}
	if (mPlanetFuture.isValid())
	{
		mPlanetDestination = mPlanetFuture;
	}
	mPlanetFuture = mWorld.getEntityManager().createEntity<Planet>(mPlanetDestination->getPosition(), mPlanetsReached);
	if (mIndicators.size() >= 2)
	{
		mIndicators[1].setEntity(mPlanetDestination);
	}

	if (mOldPlanets.size() > 3)
	{
		mOldPlanets.front().kill();
		mOldPlanets.pop();
	}

	GameSingleton::mTradeShip->setDestination(mPlanetDestination->getPosition());

	U32 size = mAsteroids.size();
	if (oe::Random::get<I32>(0, 99) > 10 && size == 0 && mPlanetsReached > 1)
	{
		mAsteroids.push_back(new AsteroidChunk(mWorld));
		mAsteroids.back()->init(mPlanetsReached + 1, mPlanetDestination->getPosition());
	}
	if (size > 0)
	{
		if (mAsteroids[0]->getStarted() + 2 <= mPlanetsReached)
		{
			mAsteroids[0]->remove();
			delete mAsteroids[0];
			size--;
			mAsteroids.clear();
		}
	}

	generateEvent();
}

void GameState::loadGUI()
{
	F32 w = getApplication().getWindow().getSize().x;
	F32 h = getApplication().getWindow().getSize().y;

	mBoostBar.setBackColor(sf::Color(172, 172, 172));
	mBoostBar.setBarColor(sf::Color::Cyan);
	mBoostBar.setOutlineColor(sf::Color(32, 32, 32));
	mBoostBar.setOutlineThickness(1.5f);
	mBoostBar.setVertical(true);
	mBoostBar.setValueMax(F32(GameSingleton::mPlayerShip->getBoostMax()));
	mBoostBar.setValue(F32(GameSingleton::mPlayerShip->getBoost()));
	mBoostBar.setSize(w * 0.08f, h * 0.4f);
	mBoostBar.setPosition(w * 0.92f, h * 0.3f);

	mLifeBar.setBackColor(sf::Color(172, 172, 172));
	mLifeBar.setBarColor(sf::Color::Green);
	mLifeBar.setOutlineColor(sf::Color(32, 32, 32));
	mLifeBar.setOutlineThickness(1.5f);
	mLifeBar.setValueMax(F32(GameSingleton::mPlayerShip->getLifeMax()));
	mLifeBar.setValue(F32(GameSingleton::mPlayerShip->getLife()));

	mArmorBar.setBackColor(sf::Color(172, 172, 172));
	mArmorBar.setBarColor(sf::Color::Cyan);
	mArmorBar.setOutlineColor(sf::Color(32, 32, 32));
	mArmorBar.setOutlineThickness(1.5f);
	mArmorBar.setValueMax(F32(GameSingleton::mPlayerShip->getArmorMax()));
	mArmorBar.setValue(F32(GameSingleton::mPlayerShip->getArmor()));

	mLifeBarTrader.setBackColor(sf::Color(172, 172, 172));
	mLifeBarTrader.setBarColor(sf::Color::Green);
	mLifeBarTrader.setOutlineColor(sf::Color(32, 32, 32));
	mLifeBarTrader.setOutlineThickness(1.5f);
	mLifeBarTrader.setValueMax(F32(GameSingleton::mTradeShip->getLifeMax()));
	mLifeBarTrader.setValue(F32(GameSingleton::mTradeShip->getLife()));
	mLifeBarTrader.setSize(w * 0.25f, h * 0.02f);
	mLifeBarTrader.setPosition(w * 0.25f, 0.0f);

	mArmorBarTrader.setBackColor(sf::Color(172, 172, 172));
	mArmorBarTrader.setBarColor(sf::Color::Cyan);
	mArmorBarTrader.setOutlineColor(sf::Color(32, 32, 32));
	mArmorBarTrader.setOutlineThickness(1.5f);
	mArmorBarTrader.setValueMax(F32(GameSingleton::mTradeShip->getArmorMax()));
	mArmorBarTrader.setValue(F32(GameSingleton::mTradeShip->getArmor()));
	mArmorBarTrader.setSize(w * 0.25f, h * 0.02f);
	mArmorBarTrader.setPosition(w * 0.5f, 0.0f);

	mLeftSprite.setTexture(getApplication().getTextures().get(GameSingleton::mHUDTexture));
	mLeftSprite.setTextureRect(sf::IntRect(0, 0, 180, 182));
	mLeftSprite.setPosition(0, 0);

	mRightSprite.setTexture(getApplication().getTextures().get(GameSingleton::mHUDTexture));
	mRightSprite.setTextureRect(sf::IntRect(180, 0, 178, 182));
	mRightSprite.setPosition(w - mRightSprite.getGlobalBounds().width, 0);

	mPlanetPanel.setTexture(getApplication().getTextures().get(GameSingleton::mHUDTexture));
	mPlanetPanel.setTextureRect(sf::IntRect(0, 182, 201, 321));
	mPlanetPanel.setScale(0.8f, 0.8f);
	mPlanetPanel.setPosition(0, h * 0.5f - mPlanetPanel.getGlobalBounds().height * 0.5f);

	mTextPlanets.setFont(getApplication().getFonts().get(GameSingleton::mFont));
	mTextPlanets.setCharacterSize(24);
	mTextPlanets.setFillColor(sf::Color::Black);
	mTextPlanets.setPosition(135, 33);

	#ifdef OE_DESKTOP
		mLifeBar.setSize(w * 0.40f, h * 0.03f);
		mLifeBar.setPosition(w * 0.1f, h * 0.97f);
		mArmorBar.setSize(w * 0.40f, h * 0.03f);
		mArmorBar.setPosition(w * 0.5f, h * 0.97f);
	#else
		mLifeBar.setSize(w * 0.25f, h * 0.03f);
		mLifeBar.setPosition(w * 0.25f, h * 0.97f);
		mArmorBar.setSize(w * 0.25f, h * 0.03f);
		mArmorBar.setPosition(w * 0.5f, h * 0.97f);
	#endif
}

void GameState::generateEvent()
{
	// Data for events
	oe::Vector2 pA = oe::Vector2(0, 0);
	if (mPlanetCurrent.isValid())
	{
		pA = mPlanetCurrent->getPosition();
	}
	oe::Vector2 pB = mPlanetDestination->getPosition();
	oe::Vector2 delta = pB - pA;
	F32 length = delta.getLength();
	F32 angle = delta.getPolarAngle();
	oe::Vector2 dir = delta.getNormal();
	oe::Vector2 ortho = dir.getRotated(90.0f);

	U32 amount = mPlanetsReached;
	U32 eventType = oe::Random::get<U32>(1, 5);
	printf("Event : %d\n", eventType);
	switch (eventType)
	{
		case 1: event1(amount, pA, angle); break; // Attack from behind
		case 2: event2(amount, pA, length, dir, ortho); break; // Attack from right side
		case 3: event3(amount, pA, length, dir, ortho); break; // Attack from left side
		case 4: event5(amount, pB, length, angle, dir); break; // Attack blockus
		case 5: event6(amount, pA, length, dir, ortho); break; // Attack ambush
	}
}

void GameState::event1(U32 amount, const oe::Vector2 & pA, F32 angle)
{
	for (U32 i = 0; i < amount; i++)
	{
		F32 angleSpawn = angle + oe::Random::get<F32>(135, 225);
		F32 lengthSpawn = GameConfig::getF("event1-var") + oe::Random::get<F32>(0.0f, 500.0f);

		spawnEnemy(amount, i, pA + oe::Vector2::polarVector(angleSpawn, lengthSpawn));
	}
}

void GameState::event2(U32 amount, const oe::Vector2 & pA, F32 length, const oe::Vector2 & dir, const oe::Vector2 & ortho)
{
	for (U32 i = 0; i < amount; i++)
	{
		F32 d = GameConfig::getF("event2-var");
		F32 r = oe::Random::getDev(0.0f, 0.25f * length);

		spawnEnemy(amount, i, pA + dir * 0.5f * length + ortho * d + dir * r);
	}
}

void GameState::event3(U32 amount, const oe::Vector2 & pA, F32 length, const oe::Vector2 & dir, const oe::Vector2 & ortho)
{
	for (U32 i = 0; i < amount; i++)
	{
		F32 d = GameConfig::getF("event3-var");
		F32 r = oe::Random::getDev(0.0f, 0.25f * length);

		spawnEnemy(amount, i, pA + dir * 0.5f * length - ortho * d + dir * r);
	}
}

void GameState::event4(U32 amount, const oe::Vector2 & pB, F32 angle)
{
	for (U32 i = 0; i < amount; i++)
	{
		F32 angleSpawn = angle + oe::Random::getDev<F32>(0, 45);
		F32 lengthSpawn = GameConfig::getF("event4-var") + oe::Random::get<F32>(0.0f, 500.0f);

		spawnEnemy(amount, i, pB + oe::Vector2::polarVector(angleSpawn, lengthSpawn));
	}
}

void GameState::event5(U32 amount, const oe::Vector2 & pB, F32 length, F32 angle, const oe::Vector2 & dir)
{
	for (U32 i = 0; i < amount; i++)
	{
		F32 angleSpawn = angle + oe::Random::getDev<F32>(0, 45);
		F32 lengthSpawn = GameConfig::getF("event5-var") + oe::Random::get<F32>(0.0f, 500.0f);

		spawnEnemy(amount, i, pB - dir * 0.8f * length + oe::Vector2::polarVector(angleSpawn, lengthSpawn));
	}
}

void GameState::event6(U32 amount, const oe::Vector2 & pA, F32 length, const oe::Vector2 & dir, const oe::Vector2& ortho)
{
	for (U32 i = 0; i < amount; i++)
	{
		F32 d = GameConfig::getF("event6-var");
		F32 r = oe::Random::getDev(0.0f, 0.25f * length);

		if (oe::Random::getBool())
		{
			d *= -1.0f;
		}

		spawnEnemy(amount, i, pA + dir * 0.5f * length + ortho * d + dir * r);
	}
}

void GameState::spawnEnemy(U32 amount, U32 index, const oe::Vector2 & position)
{
	U32 i = index % 5;
	if (i == 0 || i == 1 || i == 3)
	{
		mEnemies.push_back(mWorld.getEntityManager().createEntity<Enemy1Ship>(position));
	}
	if (i == 2)
	{
		mEnemies.push_back(mWorld.getEntityManager().createEntity<Enemy2Ship>(position));
	}
	if (i == 4)
	{
		mEnemies.push_back(mWorld.getEntityManager().createEntity<Enemy3Ship>(position));
	}
}

void GameState::clearEnemies()
{
	for (U32 i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i].kill();
	}
	mEnemies.clear();
}
