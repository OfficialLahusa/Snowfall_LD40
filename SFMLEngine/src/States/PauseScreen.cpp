#include <iostream>
#include "PauseScreen.h"
#include "../DEFINITIONS.h"
#include "MenuState.h"

namespace sse
{
	PauseScreen::PauseScreen(GameDataRef data)
		: m_data(data)
	{
	}

	bool PauseScreen::Init()
	{
		sf::Vector2u windowSize = m_data->window.getSize();
		sf::Texture texture;
		texture.create(windowSize.x, windowSize.y);
		texture.update(m_data->window);
		m_image = texture.copyToImage();
		
		m_buttons.setTexture(m_data->assets.GetTexture("pause_menu"));
		m_buttons.setScale({ SCALE_FACTOR, SCALE_FACTOR });

		m_backGroundTexture.loadFromImage(m_image);
		m_backGround.setTexture(m_backGroundTexture);
		return true;
	}

	bool PauseScreen::Terminate()
	{
		if (m_quit)
		{
			m_data->machine.AddState(StateRef(new MenuState(m_data)), true);
		}
		return true;
	}
	

	bool PauseScreen::HandleInput(float dt)
	{
		sf::Event event;
		sf::Sprite quit;
		quit.setTextureRect({ 0, 0, 120 * SCALE_FACTOR, 32 * SCALE_FACTOR });
		quit.setPosition(181 * SCALE_FACTOR, 170 * SCALE_FACTOR);

		sf::Sprite resume;
		resume.setTextureRect({ 0, 0, 120 * SCALE_FACTOR, 32 * SCALE_FACTOR });
		resume.setPosition(20 * SCALE_FACTOR, 170 * SCALE_FACTOR);

		while (m_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_data->window.close();
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			{
				m_data->machine.Pop_back();
			}
			if(event.type == sf::Event::MouseButtonReleased)
			{
				if (m_data->input.IsPointOnSprite(resume, { sf::Mouse::getPosition(m_data->window).x, sf::Mouse::getPosition(m_data->window).y }))
				{
					m_data->machine.Pop_back();
				}
				if (m_data->input.IsPointOnSprite(quit, { sf::Mouse::getPosition(m_data->window).x, sf::Mouse::getPosition(m_data->window).y }))
				{
					m_quit = true;
					m_data->machine.Pop_back();
				}
			}
		}
		return true;
	}

	bool PauseScreen::Update(float dt)
	{
		return true;
	}

	bool PauseScreen::Render(float dt)
	{
		m_data->window.clear();

		m_data->window.draw(m_backGround);
		m_data->window.draw(m_buttons);

		m_data->window.display();
		return true;
	}
}