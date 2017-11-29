#include "PopUp.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "GameConfig.hpp"
#include "GameSingleton.hpp"

PopUp::PopUp(sf::Texture& screen)
{
	mScreen.setTexture(screen);
	//mScreen.setPosition(0, 0); // move screen top
	mOpen = true;
	mExit = false;
}

bool PopUp::isOpen() const
{
	return mOpen;
}

bool PopUp::isExit() const
{
	return mExit;
}