#include "IntroState.hpp"

#include "../Engine/Application/Application.hpp"

#include "GameConfig.hpp"
#include "GameSingleton.hpp"

#include "GameState.hpp" // Used to switch to
#include "MenuState.hpp" // Used to switch to

IntroState::IntroState(oe::StateManager& manager)
	: oe::State(manager)
{
	mAtmogTexture.loadFromFile("../Assets/Textures/atmog.png");
	mAtmogSprite.setTexture(mAtmogTexture);
}

bool IntroState::handleEvent(const sf::Event& event)
{
	return false;
}

bool IntroState::update(oe::Time dt)
{
	GameSingleton::loadResources2();

	static const oe::Time duration = oe::seconds(1.0f);

	mElapsed += dt;
	if (mElapsed > duration)
	{
		getApplication().getAudio().setGlobalVolume(10.0f);

		oe::ResourceId music = getApplication().getAudio().createMusic("MainTheme", "../Assets/Musics/MainTheme.ogg");
		getApplication().getAudio().playMusic(music);

		popState();
		pushState<MenuState>();
	}
	return false;
}

void IntroState::render(sf::RenderTarget& target)
{
	target.draw(mAtmogSprite);
}
