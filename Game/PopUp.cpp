#include "PopUp.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "GameConfig.hpp"
#include "GameSingleton.hpp"

#include "MenuState.hpp"

#include "../Engine/Application/Application.hpp"

PopUp::PopUp(oe::StateManager& manager)
	: oe::State(manager)
{
	mScreen.setTexture(GameSingleton::application->getTextures().get(GameSingleton::mDeadUITexture));
	mScreen.setOrigin(210, 171);
	mScreen.setPosition(toSF(GameSingleton::application->getWindow().getSize() * 0.5f));
}

bool PopUp::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mPos = toSF(getApplication().getWindow().getCursorPosition());
		if (sf::FloatRect(mScreen.getPosition() - mScreen.getOrigin() + sf::Vector2f(51, 194), sf::Vector2f(147, 79)).contains(mPos))
		{
			popState();
		}
		else if (sf::FloatRect(mScreen.getPosition() - mScreen.getOrigin() + sf::Vector2f(214, 194), sf::Vector2f(147, 79)).contains(mPos))
		{
			popState();
			popState();
			pushState<MenuState>();
		}
	}

	return false;
}

bool PopUp::update(oe::Time dt)
{
	return false;
}

void PopUp::render(sf::RenderTarget & target)
{
	target.draw(mScreen);
}
