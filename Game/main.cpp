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
	GameConfig::loadFromFile("../config.ini");

	// Load Resources
	GameSingleton::loadResources1(application);

	application.getAudio().setMusicVolume(50.0f);
	application.getAudio().setSoundVolume(50.0f);
	
	// Load Window
	oe::Window& window = application.getWindow();
	window.create(sf::VideoMode(GameConfig::getU("win-width"), GameConfig::getU("win-height")), GameConfig::getS("win-title"), sf::Style::Close);
	//window.setIcon(ICON_144);
	//window.useCustomCursor(WINCURSOR, sf::IntRect(0, 0, 48, 48), sf::Vector2f(24, 24));
	//window.setScreenshotPath(WINSCREENSHOTS);
	window.setMainView(sf::View(sf::FloatRect(0.0f, 0.0f, 800, 600)));
	window.applyMainView();
	window.closeOnClosed();

	// Load State
	application.start<IntroState>();

	getchar();
	return 0;
}
