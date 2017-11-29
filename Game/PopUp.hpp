#ifndef POPUP_HPP
#define POPUP_HPP

#include "../Engine/System/Prerequisites.hpp"
#include "../Engine/Application/AudioSystem.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

class PopUp : public sf::Drawable
{
	public:
		PopUp(sf::Texture& screen);

		virtual void handleEvent(const sf::Event& event) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		bool isOpen() const;
		bool isExit() const;

	protected:
		sf::Sprite mScreen;
		bool mOpen;
		bool mExit;
};

#endif // POPUP_HPP
