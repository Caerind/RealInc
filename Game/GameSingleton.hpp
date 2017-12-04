#ifndef GAMESINGLETON_HPP
#define GAMESINGLETON_HPP

#include "../Engine/Graphics/Animation.hpp"
#include "../Engine/Graphics/Tileset.hpp"
#include "../Engine/Graphics/SFMLResources.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/EntityQuery.hpp"
#include "../Engine/Core/Systems/ActionSystem.hpp"
#include "../Engine/Application/AudioSystem.hpp"
#include <SFML/Window/Keyboard.hpp>

#include "PlayerShip.hpp"
#include "TradeShip.hpp"

class GameSingleton
{
	public:
		static oe::Application* application;

		static void loadResources1(oe::Application& application);
		static void loadResources2();

		static void clear();

		static oe::ResourceId mFont;

		static oe::ResourceId mIndicatorTexture;
		static oe::ResourceId mTilesetTexture;
		static oe::ResourceId mPlanetTexture;
		static oe::ResourceId mShipTexture;
		static oe::ResourceId mTradeShipTexture;
		static oe::ResourceId mProjTexture;
		static oe::ResourceId mEnemy1Texture;
		static oe::ResourceId mEnemy2Texture;
		static oe::ResourceId mEnemy3Texture;
		static oe::ResourceId mHUDTexture;
		static oe::ResourceId mParticleTexture;
		static oe::ResourceId mAsteroidsTexture;
		static oe::ResourceId mAsteroidsLargeTexture;
		static oe::ResourceId mUIBackTexture;
		static oe::ResourceId mUITopTexture;
		static oe::ResourceId mDeadUITexture;
		static oe::ResourceId mMenuUITexture;

		static oe::ResourceId mAsteroidSound;
		static oe::ResourceId mExplosionSound;
		static oe::ResourceId mShieldSound;
		static oe::ResourceId mShoot1Sound;
		static oe::ResourceId mShoot2Sound;
		static oe::ResourceId mClickSound;
		static std::shared_ptr<sf::Sound> mEngineSoundManager;

		static oe::EntityHandle mPlayerHandle;
		static oe::EntityHandle mTradeHandle;
		static PlayerShip* mPlayerShip;
		static TradeShip* mTradeShip;
		static oe::EntityQuery mEntityQuery;

		static bool mIsOnTrade;
		static bool mRestart;

		static U32 mMoney;
		static U32 mResource1;
		static U32 mResource2;
		static U32 mResource3;
		static U32 mBuyIndexes[6];

		static F32 mPlayerBoost;
		static I32 mPlayerLife;
		static I32 mPlayerArmor;

		static U32 mTraderCapacity;
		static I32 mTraderLife;
		static I32 mTraderArmor;

		static void playSound(oe::ResourceId r, const oe::Vector2& position);
		static void playClick();

};

#endif // GAMESINGLETON_HPP
