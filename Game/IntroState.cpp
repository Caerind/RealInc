#include "IntroState.hpp"

#include "../Engine/Application/Application.hpp"

#include "GameConfig.hpp"
#include "GameSingleton.hpp"

#include "GameState.hpp" // Used to switch to
//#include "MenuState.hpp" // Used to switch to

IntroState::IntroState(oe::StateManager& manager)
	: oe::State(manager)
{
	//mAtmogTexture.loadFromFile(TEXTURE_ATMOG);
	mAtmogSprite.setTexture(mAtmogTexture);
}

bool IntroState::handleEvent(const sf::Event& event)
{
	return false;
}

bool IntroState::update(oe::Time dt)
{
	GameSingleton::loadResources2();

	static const oe::Time duration = oe::seconds(0.001f);

	mElapsed += dt;
	if (mElapsed > duration)
	{
		popState();
		pushState<GameState>();
		//pushState<MenuState>();
	}
	return false;
}

void IntroState::render(sf::RenderTarget& target)
{
	target.draw(mAtmogSprite);
}
