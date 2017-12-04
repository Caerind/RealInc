#ifndef POPUP_HPP
#define POPUP_HPP

#include "../Engine/System/Prerequisites.hpp"
#include "../Engine/Application/AudioSystem.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "../Engine/Application/StateManager.hpp"

class PopUp : public oe::State
{
	public:
		PopUp(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

	protected:
		sf::Sprite mScreen;
};

#endif // POPUP_HPP
