#include "GameSingleton.hpp"
#include "../Engine/Application/Application.hpp"
#include "GameConfig.hpp"

oe::Application* GameSingleton::application;

oe::ResourceId GameSingleton::mFont;

oe::ResourceId GameSingleton::mIndicatorTexture;
oe::ResourceId GameSingleton::mTilesetTexture;
oe::ResourceId GameSingleton::mPlanetTexture;
oe::ResourceId GameSingleton::mShipTexture;
oe::ResourceId GameSingleton::mTradeShipTexture;
oe::ResourceId GameSingleton::mProjTexture;
oe::ResourceId GameSingleton::mEnemy1Texture;
oe::ResourceId GameSingleton::mEnemy2Texture;
oe::ResourceId GameSingleton::mEnemy3Texture;
oe::ResourceId GameSingleton::mHUDTexture;
oe::ResourceId GameSingleton::mParticleTexture;
oe::ResourceId GameSingleton::mAsteroidsTexture;
oe::ResourceId GameSingleton::mAsteroidsLargeTexture;
oe::ResourceId GameSingleton::mUIBackTexture;
oe::ResourceId GameSingleton::mUITopTexture;
oe::ResourceId GameSingleton::mDeadUITexture;
oe::ResourceId GameSingleton::mMenuUITexture;

oe::ResourceId GameSingleton::mAsteroidSound;
oe::ResourceId GameSingleton::mExplosionSound;
oe::ResourceId GameSingleton::mShieldSound;
oe::ResourceId GameSingleton::mShoot1Sound;
oe::ResourceId GameSingleton::mShoot2Sound;
oe::ResourceId GameSingleton::mClickSound;
std::shared_ptr<sf::Sound> GameSingleton::mEngineSoundManager;

oe::EntityHandle GameSingleton::mPlayerHandle;
oe::EntityHandle GameSingleton::mTradeHandle;
PlayerShip* GameSingleton::mPlayerShip;
TradeShip* GameSingleton::mTradeShip;
oe::EntityQuery GameSingleton::mEntityQuery;

bool GameSingleton::mIsOnTrade;
bool GameSingleton::mRestart;

U32 GameSingleton::mMoney;
U32 GameSingleton::mResource1;
U32 GameSingleton::mResource2;
U32 GameSingleton::mResource3;
U32 GameSingleton::mBuyIndexes[];
F32 GameSingleton::mPlayerBoost;
I32 GameSingleton::mPlayerLife;
I32 GameSingleton::mPlayerArmor;
U32 GameSingleton::mTraderCapacity;
I32 GameSingleton::mTraderLife;
I32 GameSingleton::mTraderArmor;

void GameSingleton::loadResources1(oe::Application& application)
{
	GameSingleton::application = &application;
}

void GameSingleton::loadResources2()
{
	// Font
	mFont = application->getFonts().create("sansation", oe::FontLoader::loadFromFile("../Assets/Fonts/ErasBoldITC.ttf"));

	// Textures
	mIndicatorTexture = application->getTextures().create("indicator", oe::TextureLoader::loadFromFile("../Assets/Textures/indicator.png"));
	application->getTextures().get(mIndicatorTexture).setSmooth(true);
	mTilesetTexture = application->getTextures().create("tileset", oe::TextureLoader::loadFromFile("../Assets/Textures/tileset.png"));
	application->getTextures().get(mTilesetTexture).setRepeated(true);
	mPlanetTexture = application->getTextures().create("planet", oe::TextureLoader::loadFromFile("../Assets/Textures/planet.png"));
	application->getTextures().get(mPlanetTexture).setSmooth(true);
	mShipTexture = application->getTextures().create("ship", oe::TextureLoader::loadFromFile("../Assets/Textures/ship.png"));
	application->getTextures().get(mShipTexture).setSmooth(true);
	mTradeShipTexture = application->getTextures().create("tradeship", oe::TextureLoader::loadFromFile("../Assets/Textures/tradeship.png"));
	application->getTextures().get(mTradeShipTexture).setSmooth(true);
	mProjTexture = application->getTextures().create("projectile", oe::TextureLoader::loadFromFile("../Assets/Textures/projectile.png"));
	application->getTextures().get(mProjTexture).setSmooth(true);
	mEnemy1Texture = application->getTextures().create("enemy-1", oe::TextureLoader::loadFromFile("../Assets/Textures/enemyship-1.png"));
	application->getTextures().get(mEnemy1Texture).setSmooth(true);
	mEnemy2Texture = application->getTextures().create("enemy-2", oe::TextureLoader::loadFromFile("../Assets/Textures/enemyship-2.png"));
	application->getTextures().get(mEnemy2Texture).setSmooth(true);
	mEnemy3Texture = application->getTextures().create("enemy-3", oe::TextureLoader::loadFromFile("../Assets/Textures/enemyship-3.png"));
	application->getTextures().get(mEnemy3Texture).setSmooth(true);
	mHUDTexture = application->getTextures().create("hud", oe::TextureLoader::loadFromFile("../Assets/Textures/hud.png"));
	application->getTextures().get(mHUDTexture).setSmooth(true);
	mParticleTexture = application->getTextures().create("particle", oe::TextureLoader::loadFromFile("../Assets/Textures/particle.png"));
	application->getTextures().get(mParticleTexture).setSmooth(true);
	mAsteroidsTexture = application->getTextures().create("asteroids", oe::TextureLoader::loadFromFile("../Assets/Textures/asteroids.png"));
	application->getTextures().get(mAsteroidsTexture).setSmooth(true);
	mAsteroidsLargeTexture = application->getTextures().create("asteroidslarge", oe::TextureLoader::loadFromFile("../Assets/Textures/asteroids-large.png"));
	application->getTextures().get(mAsteroidsLargeTexture).setSmooth(true);
	mUIBackTexture = application->getTextures().create("ui-back", oe::TextureLoader::loadFromFile("../Assets/Textures/trade-ui-back.png"));
	application->getTextures().get(mUIBackTexture).setSmooth(true);
	mUITopTexture = application->getTextures().create("ui-top", oe::TextureLoader::loadFromFile("../Assets/Textures/trade-ui-top.png"));
	application->getTextures().get(mUITopTexture).setSmooth(true);
	mDeadUITexture = application->getTextures().create("ui-dead", oe::TextureLoader::loadFromFile("../Assets/Textures/dead-ui.png"));
	application->getTextures().get(mDeadUITexture).setSmooth(true);
	mMenuUITexture = application->getTextures().create("ui-menu", oe::TextureLoader::loadFromFile("../Assets/Textures/menu-ui.png"));
	application->getTextures().get(mMenuUITexture).setSmooth(true);

	// Sound
	mAsteroidSound = application->getAudio().createSound("asteroid", "../Assets/Sounds/asteroid.wav");
	mExplosionSound = application->getAudio().createSound("explosion", "../Assets/Sounds/explosion.wav");
	mShieldSound = application->getAudio().createSound("shield", "../Assets/Sounds/shield.wav");
	mShoot1Sound = application->getAudio().createSound("shoot-1", "../Assets/Sounds/shoot-1.wav");
	mShoot2Sound = application->getAudio().createSound("shoot-2", "../Assets/Sounds/shoot-2.wav");
	mClickSound = application->getAudio().createSound("click", "../Assets/Sounds/click.wav");
}

void GameSingleton::clear()
{
	mPlayerHandle.invalidate();
	mTradeHandle.invalidate();
	mPlayerShip = nullptr;
	mTradeShip = nullptr;

	mIsOnTrade = false;
	mRestart = false;

	mMoney = GameConfig::getU("money-start");
	mResource1 = 0;
	mResource2 = 0;
	mResource3 = 0;
	for (U32 i = 0; i < 6; i++)
	{
		mBuyIndexes[i] = 0;
	}

	mPlayerBoost = GameConfig::getF("player-boost");
	mPlayerLife = GameConfig::getI("player-life");
	mPlayerArmor = GameConfig::getI("player-armor");

	mTraderCapacity = GameConfig::getU("trader-capacity");
	mTraderLife = GameConfig::getI("trader-life");
	mTraderArmor = GameConfig::getI("trader-armor");
}

void GameSingleton::playSound(oe::ResourceId r, const oe::Vector2& position)
{
	bool play = true;
	if (r != mShoot1Sound)
	{
		if ((mPlayerShip->getPosition() - position).getLength() > 1200.0f)
		{
			play = false;
		}
	}
	if (play)
	{
		application->getAudio().playSound(r)->setVolume(20.0f);
	}
}

void GameSingleton::playClick()
{
	application->getAudio().playSound(mClickSound)->setVolume(20.0f);
}
