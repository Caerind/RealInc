#include "PreState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Application/Application.hpp"

#include "GameState.hpp"

PreState::PreState(oe::StateManager& manager)
	: oe::State(manager)
{

	mTexture.loadFromFile("../Assets/Textures/pre-ui-1.png");
	mScreen.setTexture(mTexture);

	mI = 0;
	
}

bool PreState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mpos((F32)event.mouseButton.x, (F32)event.mouseButton.y);

		if (mI == 0)
		{
			mTexture.loadFromFile("../Assets/Textures/pre-ui-2.png");
			mScreen.setTexture(mTexture);

			mI++;
		}
		else if (mI == 1)
		{
			mTexture.loadFromFile("../Assets/Textures/pre-ui-3.png");
			mScreen.setTexture(mTexture);

			mI++;
		}
		else if (mI == 2)
		{
			popState();
			pushState<GameState>();
		}
	}

	return false;
}

bool PreState::update(oe::Time dt)
{
	return false;
}

void PreState::render(sf::RenderTarget& target)
{
	target.draw(mScreen);
}