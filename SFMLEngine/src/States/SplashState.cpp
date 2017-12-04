#include <iostream>
#include "SplashState.h"
#include "../DEFINITIONS.h"
#include "MenuState.h"

namespace sse
{
	SplashState::SplashState(GameDataRef data)
		: m_data(data)
		, m_pixel_threshold(0.06f)
	{
	}

	bool SplashState::Init()
	{
		m_data->window.setVerticalSyncEnabled(true);
	
		//SplashState loading
		m_data->assets.LoadShaderFile("pixelate", SHADE_PIXELATE_FILEPATH);
		m_data->assets.LoadTexture("logo", LOGO_FILEPATH);

		//Main menu loading
		m_data->assets.LoadTexture("main_menu", MAIN_MENU_FILEPATH);

		//game loading
		m_data->assets.LoadTexture("map_texture", TILE_FILEPATH);
		m_data->assets.LoadTexture("bucket_empty", BUCKET_EMPTY_FILEPATH);
		m_data->assets.LoadTexture("bucket_slightly_empty", BUCKET_SLIGHTLY_FULL_FILEPATH);
		m_data->assets.LoadTexture("bucket_half_full", BUCKET_HALF_FULL_FILEPATH);
		m_data->assets.LoadTexture("bucket_full", BUCKET_FULL_FILEPATH);
		m_data->assets.LoadTexture("flacke", FLACKE_FILEPATH);
		m_data->assets.LoadTexture("shadow", SHADOW_FILEPATH);
		m_data->assets.LoadTexture("hauses", HAUSES_FILEPATH);
		m_data->assets.LoadTexture("player_static", PLAYER_STATIC_FILEPATH);
		m_data->assets.LoadTexture("player_static_empty", PLAYER_STATIC_EMPTY_FILEPATH);
		m_data->assets.LoadTexture("player_static_slightly_full", PLAYER_STATIC_SLIGHTLY_FULL_FILEPATH);
		m_data->assets.LoadTexture("player_static_half_full", PLAYER_STATIC_HALF_FULL_FILEPATH);
		m_data->assets.LoadTexture("pause_menu", PAUSE_MENUE_FILEPATH);
		m_data->assets.LoadFont("font", FONT_FILEPATH);
		m_data->assets.LoadFont("tutorial_font", TUTORIAL_FONT_FILEPATH);
		//gameOver loading
		m_data->assets.LoadTexture("gameOver", GAME_OVER_BACK_GROUND_FILEPATH);

		m_background.setTexture(m_data->assets.GetTexture("logo"));
		m_data->assets.GetShader("pixelate").setUniform("texture", sf::Shader::CurrentTexture);
		m_background.setScale({ SCALE_FACTOR, SCALE_FACTOR });
		return true;
	}

	bool SplashState::HandleInput(float dt)
	{
		sf::Event event;

		
		while (m_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_data->window.close();
			}
		}
		return true;
	}

	bool SplashState::Update(float dt)
	{
		if (m_pixel_threshold >= 0.0f)
		{
			m_pixel_threshold -= 0.025f * dt;
		}
		else
		{
			m_pixel_threshold = 0.0f;
		}
		
		m_data->assets.GetShader("pixelate").setUniform("pixel_threshold", m_pixel_threshold);

		if (m_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			m_data->machine.AddState(StateRef(new MenuState(m_data)), true);
		}
		return true;
	}

	bool SplashState::Render(float dt)
	{
		m_data->window.clear(sf::Color::White);

		m_data->window.draw(m_background, &m_data->assets.GetShader("pixelate"));

		m_data->window.display();
		return true;
	}
}