#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../Engine/Application/StateManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public oe::State
{
	public:
		MenuState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

	private:
		sf::Sprite mBackground;
		sf::RectangleShape mOk;
		sf::Text mTitle;
		sf::Text mTutorialText;
		sf::RectangleShape mOkTut;
		sf::RectangleShape mSpaceCheat;
		bool mSoundEnabled;
		bool mTutorialEnabled;
		bool mTutorialShow;
};

#endif // MENUSTATE_HPP
