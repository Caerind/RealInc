#include "MenuState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"
#include "PreState.hpp" // Used to switch to
#include "GameState.hpp" // Used to switch to

#include "../Engine/Math/Math.hpp"
#include "../Engine/Math/Vector2.hpp"

#include "../Engine/Application/Application.hpp"

MenuState::MenuState(oe::StateManager& manager)
	: oe::State(manager)
{
	mBackground.setTexture(getApplication().getTextures().get(GameSingleton::mMenuUITexture));

	mOk.setSize(sf::Vector2f(42, 42));
	mOk.setPosition(910, 690);
	mOk.setFillColor(sf::Color(60, 60, 60));

	mOkTut.setSize(sf::Vector2f(42, 42));
	mOkTut.setPosition(909, 522);
	mOkTut.setFillColor(sf::Color(60, 60, 60));

	mSpaceCheat.setSize(sf::Vector2f(80, 80));
	mSpaceCheat.setPosition(890, 507);
	mSpaceCheat.setFillColor(sf::Color::Black);

	mSoundEnabled = true;

	mTitle.setString(GameConfig::getS("win-title"));
	mTitle.setCharacterSize(80);
	mTitle.setFont(getApplication().getFonts().get(GameSingleton::mFont));
	mTitle.setPosition(512, 230);
	mTitle.setFillColor(sf::Color::Black);
	mTitle.setOutlineColor(sf::Color::White);
	mTitle.setOutlineThickness(5.0f);
	mTitle.setOrigin(mTitle.getGlobalBounds().width * 0.5f, mTitle.getGlobalBounds().height * 0.5f);

	mTutorialText.setString("Tutorial");
	mTutorialText.setCharacterSize(40);
	mTutorialText.setFont(getApplication().getFonts().get(GameSingleton::mFont));
	mTutorialText.setPosition(910 + 21, 465);
	mTutorialText.setFillColor(sf::Color::White);
	mTutorialText.setOrigin(mTutorialText.getGlobalBounds().width * 0.5f, mTutorialText.getGlobalBounds().height * 0.5f);
	mTutorialText.setStyle(sf::Text::Style::Italic);

	static bool first = true;
	if (first == true)
	{
		mTutorialShow = false;
		mTutorialEnabled = true;
		first = false;
	}
	else
	{
		mTutorialEnabled = false;
		mTutorialShow = true;
	}

}

bool MenuState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mpos((F32)event.mouseButton.x, (F32)event.mouseButton.y);

		if (sf::FloatRect(286, 399, 441, 112).contains(mpos))
		{
			popState(); 
			if (mTutorialEnabled)
			{
				pushState<PreState>();
			}
			else
			{
				pushState<GameState>();
			}
		}
		
		if (sf::FloatRect(286, 555, 446, 108).contains(mpos))
		{
			getApplication().getWindow().close();
			getApplication().getAudio().stop();
			getApplication().clearStates();
		}

		if (sf::FloatRect(892, 673, 81, 74).contains(mpos))
		{
			if (mSoundEnabled)
			{
				getApplication().getAudio().setGlobalVolume(0.0f);
			}
			else
			{
				getApplication().getAudio().setGlobalVolume(10.0f);
			}
			mSoundEnabled = !mSoundEnabled;
		}

		if (sf::FloatRect(890, 507, 81, 74).contains(mpos) && mTutorialShow)
		{
			mTutorialEnabled = !mTutorialEnabled;
		}


	}
	return false;
}

bool MenuState::update(oe::Time dt)
{
	return false;
}

void MenuState::render(sf::RenderTarget& target)
{
	target.draw(mBackground);

	if (mSoundEnabled)
	{
		target.draw(mOk);
	}

	target.draw(mTitle);

	if (mTutorialShow)
	{
		target.draw(mTutorialText);
		if (mTutorialEnabled)
		{
			target.draw(mOkTut);
		}
	}
	else
	{
		target.draw(mSpaceCheat);
	}
}
