#include <iostream>
#include "GameOverState.h"
#include "../DEFINITIONS.h"
#include "MenuState.h"
#include <string>

namespace sse
{
	GameOverState::GameOverState(GameDataRef data, size_t score)
		: m_data(data)
		, m_score(score)
	{
	}

	bool GameOverState::Init()
	{
		m_background.setTexture(m_data->assets.GetTexture("gameOver"));
		m_background.setScale({ SCALE_FACTOR, SCALE_FACTOR });

		m_scoreText.setFont(m_data->assets.GetFont("font"));
		if (m_score == 0)
		{
			m_scoreText.setString(" You didn't catch any snowflakes.\n\t\t\t Better luck next time.");
		}
		else if (m_score == 1)
		{
			m_scoreText.setString("\t\t\tYou caught " + std::to_string(m_score) + " snowflake.");
		}
		else
		{
			m_scoreText.setString("\t\t\tYou caught " + std::to_string(m_score) + " snowflakes.");
		}
		m_scoreText.setFillColor(sf::Color(0, 0, 0));
		m_scoreText.setCharacterSize(26);
		m_scoreText.setPosition(0, 0);


		return true;
	}

	bool GameOverState::HandleInput(float dt)
	{
		sf::Event event;


		while (m_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_data->window.close();
			}
			else if (event.type == sf::Event::KeyReleased && m_clock.getElapsedTime().asSeconds() > GAME_OVER_BACK_SHOW_TIME)
			{
				m_data->machine.AddState(StateRef(new MenuState(m_data)), true);
			}
			else if (event.type == sf::Event::MouseButtonReleased && m_clock.getElapsedTime().asSeconds() > GAME_OVER_BACK_SHOW_TIME)
			{
				m_data->machine.AddState(StateRef(new MenuState(m_data)), true);
			}
		}
		return true;
	}

	bool GameOverState::Update(float dt)
	{

		return true;
	}

	bool GameOverState::Render(float dt)
	{
		m_data->window.clear();

		m_data->window.draw(m_background);
		m_data->window.draw(m_scoreText);

		m_data->window.display();
		return true;
	}
}