#include <iostream>
#include "MenuState.h"
#include "../DEFINITIONS.h"
#include "GameState.h"
#include "TutorialState.h"

namespace sse
{
	MenuState::MenuState(GameDataRef data)
		: m_data(data)
	{
	}

	bool MenuState::Init()
	{
		m_backGround.setTexture(m_data->assets.GetTexture("main_menu"));
		m_backGround.setScale({ SCALE_FACTOR, SCALE_FACTOR });
		return true;
	}

	bool MenuState::HandleInput(float dt)
	{
		sf::Event event;

		sf::Sprite playButton;
		playButton.setTextureRect({ 0, 0, 119, 32 });
		playButton.setScale({ SCALE_FACTOR, SCALE_FACTOR });
		playButton.setPosition(102 * SCALE_FACTOR, 96 * SCALE_FACTOR);

		sf::Sprite tutorialButton;
		tutorialButton.setTextureRect({ 0, 0, 119, 32 });
		tutorialButton.setScale({ SCALE_FACTOR, SCALE_FACTOR });
		tutorialButton.setPosition(33 * SCALE_FACTOR, 144 * SCALE_FACTOR);

		sf::Sprite quitButton;
		quitButton.setTextureRect({ 0, 0, 119, 32 });
		quitButton.setScale({ SCALE_FACTOR, SCALE_FACTOR });
		quitButton.setPosition(168 * SCALE_FACTOR, 144 * SCALE_FACTOR);

		while (m_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_data->window.close();
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (m_data->input.IsCursorOnSprite(playButton, m_data->window))
				{
					m_data->machine.AddState(StateRef(new GameState(m_data)), true);
				}
				if (m_data->input.IsCursorOnSprite(tutorialButton, m_data->window))
				{
					m_data->machine.AddState(StateRef(new TutorialState(m_data)), true);
				}
				if (m_data->input.IsCursorOnSprite(quitButton, m_data->window))
				{
					return false;
				}
			}
		}
		return true;
	}

	bool MenuState::Update(float dt)
	{
		return true;
	}

	bool MenuState::Render(float dt)
	{
		m_data->window.clear();

		m_data->window.draw(m_backGround);

		m_data->window.display();
		return true;
	}
}