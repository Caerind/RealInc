#ifndef GAMESINGLETON_HPP
#define GAMESINGLETON_HPP

#include "../Engine/Graphics/Animation.hpp"
#include "../Engine/Graphics/Tileset.hpp"
#include "../Engine/Graphics/SFMLResources.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/Systems/ActionSystem.hpp"
#include "../Engine/Application/AudioSystem.hpp"
#include <SFML/Window/Keyboard.hpp>

class GameSingleton
{
	public:
		static oe::Application* application;

		// Loading
		static void loadResources1(oe::Application& application);
		static void loadResources2();

		// Clear the singleton before a new game
		static void clear();
};

#endif // GAMESINGLETON_HPP
