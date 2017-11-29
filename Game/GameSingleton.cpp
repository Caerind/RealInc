#include "GameSingleton.hpp"
#include "../Engine/Application/Application.hpp"

oe::Application* GameSingleton::application;

void GameSingleton::loadResources1(oe::Application& application)
{
	GameSingleton::application = &application;
}

void GameSingleton::loadResources2()
{
}

void GameSingleton::clear()
{
}