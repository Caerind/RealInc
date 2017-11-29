#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/World.hpp"

#include "Bar.hpp"
#include "PopUp.hpp"
#include "WritingText.hpp"

class GameState : public oe::State
{
	public:
		GameState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

		static void load();
		static void save();

	private:
		inline oe::Window& getWindow();
		inline oe::View& getView();
		void popUpEvent(const sf::Event& event);

	private:
		oe::World mWorld;
		oe::Time mDuration;
		oe::ImGuiProfiler mProfiler;

};

#endif // GAMESTATE_HPP
