#include "../Engine/Application/Application.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "GameState.hpp"
#include "IntroState.hpp"
#include "MenuState.hpp"

int main()
{
	oe::Application application;

	// Load Config
	GameConfig::loadFromInternal();

	// Load Resources
	GameSingleton::loadResources1(application);
	
	// Load Window
	oe::Window& window = application.getWindow();
	window.create(sf::VideoMode(GameConfig::getU("win-width"), GameConfig::getU("win-height")), GameConfig::getS("win-title"), sf::Style::Close);
	window.setIcon("../Assets/Icons/icon-144.png");
	window.useCustomCursor("../Assets/Textures/cursor.png", sf::IntRect(0, 0, 24, 24), sf::Vector2f(12, 12));
	window.setScreenshotPath("../");
	window.setMainView(sf::View(sf::FloatRect(0.0f, 0.0f, GameConfig::getF("win-width"), GameConfig::getF("win-height"))));
	window.applyMainView();
	window.closeOnClosed();

	// Load State
	application.start<IntroState>();

	getchar();
	return 0;
}
