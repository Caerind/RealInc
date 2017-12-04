#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <queue>

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/World.hpp"

#include "GameConfig.hpp"

#include "TradeState.hpp"
#include "PopUp.hpp"

#include "Bar.hpp"
#include "PopUp.hpp"
#include "WritingText.hpp"

#include "SpaceMap.hpp"
#include "Planet.hpp"
#include "Ship.hpp"
#include "PlayerShip.hpp"
#include "TradeShip.hpp"
#include "Indicator.hpp"
#include "EnemyShip.hpp"
#include "Asteroids.hpp"

class GameState : public oe::State
{
	public:
		GameState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

	private:
		inline oe::Window& getWindow();
		inline oe::View& getView();
		void devEvent(const sf::Event& event);

		void leavePlanet();

		void loadGUI();

		void generateEvent();

		void event1(U32 amount, const oe::Vector2& pA, F32 angle);
		void event2(U32 amount, const oe::Vector2& pA, F32 length, const oe::Vector2& dir, const oe::Vector2& ortho);
		void event3(U32 amount, const oe::Vector2& pA, F32 length, const oe::Vector2& dir, const oe::Vector2& ortho);
		void event4(U32 amount, const oe::Vector2& pB, F32 angle);
		void event5(U32 amount, const oe::Vector2& pB, F32 length, F32 anlge, const oe::Vector2& dir);
		void event6(U32 amount, const oe::Vector2& pA, F32 length, const oe::Vector2& dir, const oe::Vector2& ortho);

		void spawnEnemy(U32 amount, U32 index, const oe::Vector2& position);

		void clearEnemies();

	private:
		oe::World mWorld;
		oe::Time mDuration;
		oe::ImGuiProfiler mProfiler;
		ConfigWindow mConfig;

		std::queue<oe::EntityHandle> mOldPlanets;
		oe::EntityHandle mPlanetCurrent;
		oe::EntityHandle mPlanetDestination;
		oe::EntityHandle mPlanetFuture;
		U32 mPlanetsReached;
		bool mIsOnPlanet;

		std::vector<Indicator> mIndicators;
		std::vector<AsteroidChunk*> mAsteroids;

		Bar mBoostBar;
		Bar mLifeBar;
		Bar mArmorBar;
		Bar mLifeBarTrader;
		Bar mArmorBarTrader;
		sf::Sprite mLeftSprite;
		sf::Sprite mRightSprite;
		sf::Sprite mPlanetPanel;
		sf::Text mTextPlanets;

		oe::Time mSpawnerLimit;

		std::vector<oe::EntityHandle> mEnemies;

};

#endif // GAMESTATE_HPP
