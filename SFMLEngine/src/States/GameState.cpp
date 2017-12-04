#include <iostream>
#include "GameState.h"
#include "../DEFINITIONS.h"
#include "GameOverState.h"
#include "PauseScreen.h"

namespace sse
{
	static sf::Music s_backgroundMusic;

	GameState::GameState(GameDataRef data)
		: m_data(data)
		, m_map(NUM_TILES_X * NUM_TILES_Y)
		, m_player(data)
	{
		
	}

	bool GameState::Terminate()
	{
		s_backgroundMusic.setLoop(false);
		s_backgroundMusic.pause();
		s_backgroundMusic.stop();
		return true;
	}



	bool GameState::Init()
	{
		m_hauses.setTexture(m_data->assets.GetTexture("hauses"));
		m_hauses.setScale(SCALE_FACTOR, SCALE_FACTOR);
		

		s_backgroundMusic.openFromFile(BACK_GROUND_MUSIC_FILEPATH);
		s_backgroundMusic.play();
		s_backgroundMusic.setLoop(true);
		s_backgroundMusic.setVolume(15);

		m_scoreText.setFont(m_data->assets.GetFont("font"));
		m_scoreText.setCharacterSize(26);
		m_scoreText.setPosition(SCREEN_WIDTH - m_scoreText.getCharacterSize() - 100.0f, 10.0f);
		m_scoreText.setFillColor(sf::Color(0, 0, 0));
		m_scoreText.setString(std::to_string(m_score));

		for (size_t x = 0; x < NUM_TILES_X; x++)
		{
			for (size_t y = 0; y < NUM_TILES_Y; y++)
			{
				m_map[y * NUM_TILES_X + x].shape.setTexture(m_data->assets.GetTexture("map_texture"));
				m_map[y * NUM_TILES_X + x].shape.setScale(SCALE_FACTOR, SCALE_FACTOR);
				m_map[y * NUM_TILES_X + x].shape.setPosition(32.0f * SCALE_FACTOR * x, 32.0f * SCALE_FACTOR * y + SCREEN_HEIGHT - MAP_HEIGHT);
			}
		}

		size_t bucket0 = m_rng.randomInteger<size_t>(0, m_map.size());
		size_t bucket1 = m_rng.randomInteger<size_t>(0, m_map.size());
		while (bucket0 == bucket1)
		{
			bucket1 = m_rng.randomInteger<size_t>(0, m_map.size());
		}
		size_t bucket2 = m_rng.randomInteger<size_t>(0, m_map.size());
		while (bucket0 == bucket2 && bucket1 == bucket2)
		{
			bucket2 = m_rng.randomInteger<size_t>(0, m_map.size());
		}

		m_map[bucket0].bucketSnow = 0;
		m_map[bucket1].bucketSnow = 0;
		m_map[bucket2].bucketSnow = 0;

		m_player.setSpeed(125.0f * SCALE_FACTOR);

		for (size_t i = 0; i < 2; i++)
		{
			m_snow.emplace_back(m_data, static_cast<float>(m_rng.randomInteger<int>(0, NUM_TILES_X - 1)), static_cast<float>(m_rng.randomInteger<int>(0, NUM_TILES_Y - 1)), static_cast<float>(m_rng.randomInteger<int>(MAP_HEIGHT * 2, 4 * MAP_HEIGHT)), 75.0f * SCALE_FACTOR);
		}
		return true;
	}

	bool GameState::HandleInput(float dt)
	{
		sf::Event event;


		while (m_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_data->window.close();
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_data->machine.AddState(StateRef(new PauseScreen(m_data)), false);
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Sprite playerPosSprite;
					playerPosSprite.setTextureRect({ 0, 0, 32 * SCALE_FACTOR * 2, 32 * SCALE_FACTOR * 2 });
					playerPosSprite.setOrigin(32 * SCALE_FACTOR, 32 * SCALE_FACTOR);
					playerPosSprite.setPosition(m_player.getSprite().getPosition());
					for (size_t i = 0; i < m_map.size(); i++)
					{
						if (m_player.getBucket() >= 0 && m_map[i].bucketSnow == -1 && !m_data->input.IsPointOnSprite(m_map[i].shape, { static_cast<int>(m_player.getSprite().getPosition().x), static_cast<int>(m_player.getSprite().getPosition().y) }) && m_data->input.IsPointOnSprite(m_map[i].shape, { event.mouseButton.x, event.mouseButton.y }) && Collision::CircleTest(playerPosSprite, m_map[i].shape))
						{
							m_map[i].bucketSnow = m_player.getBucket();
							m_player.setSnow(-1);
						}
						else if (m_player.getBucket() == -1 && m_map[i].bucketSnow < 3 && m_data->input.IsPointOnSprite(m_map[i].shape, { event.mouseButton.x, event.mouseButton.y }) && Collision::CircleTest(playerPosSprite, m_map[i].shape))
						{
							m_player.setSnow(m_map[i].bucketSnow);
							m_map[i].bucketSnow = -1;
						}
						else if(m_player.getBucket() == -1 && m_map[i].bucketSnow == 3)
						{
							m_map[i].bucketSnow = 4;
							m_player.setSnow(0);
						}
					}
				}
				
			}
		}

		for (size_t i = 0; i < m_map.size(); i++)
		{
			if (m_player.getBucket() == -1 && m_map[i].bucketSnow == 3)
			{
				m_map[i].bucketSnow = 4;
				m_player.setSnow(0);
			}
		}

		return true;
	}

	bool GameState::Update(float dt)
	{
		m_player.update(dt, m_map);
		
		for (auto it = m_snow.begin(); it != m_snow.end(); it++)
		{
			if (it->isDead())
			{
				if (m_map[static_cast<int>(it->getPos().y) * NUM_TILES_X + static_cast<int>(it->getPos().x)].bucketSnow >= 0)
				{
					if (m_map[static_cast<int>(it->getPos().y) * NUM_TILES_X + static_cast<int>(it->getPos().x)].bucketSnow < 3)
					{
						m_map[static_cast<int>(it->getPos().y) * NUM_TILES_X + static_cast<int>(it->getPos().x)].bucketSnow += 1;
					}
				}
				else
				{
					m_data->machine.AddState(StateRef(new GameOverState(m_data, m_score)), true);
				}
				m_score++;
				m_snow.erase(it);
				m_snow.emplace_back(m_data, static_cast<float>(m_rng.randomInteger<int>(0, NUM_TILES_X - 1)), static_cast<float>(m_rng.randomInteger<int>(0, NUM_TILES_Y - 1)), static_cast<float>(m_rng.randomInteger<int>(MAP_HEIGHT * 2, 4 * MAP_HEIGHT)), 75.0f * SCALE_FACTOR);
				break;
			}
			else
			{
				it->update(dt);
			}
		}
		
		m_scoreText.setString(std::to_string(m_score));

		

		return true;
	}

	bool GameState::Render(float dt)
	{
		m_data->window.clear();
		m_data->window.draw(m_hauses);
		for (size_t x = 0; x < NUM_TILES_X; x++)
		{
			for (size_t y = 0; y < NUM_TILES_Y; y++)
			{
				m_data->window.draw(m_map[y * NUM_TILES_X + x].shape);
				if (m_map[y * NUM_TILES_X + x].bucketSnow >= 0)
				{
					sf::RectangleShape s;
					
					switch (m_map[y * NUM_TILES_X + x].bucketSnow)
					{
					case 0:
					{
						s.setTexture(&m_data->assets.GetTexture("bucket_empty"));
					}
					break;

					case 1:
					{
						s.setTexture(&m_data->assets.GetTexture("bucket_slightly_empty"));
					}
					break;

					case 2:
					{
						s.setTexture(&m_data->assets.GetTexture("bucket_half_full"));
					}
					break;

					case 3:
					{
						s.setTexture(&m_data->assets.GetTexture("bucket_full"));
					}
					break;

					default:
					{
						s.setTexture(&m_data->assets.GetTexture("bucket_full"));
					}
					break;
					}
					s.setSize({ 32.0f * SCALE_FACTOR, 32.0f * SCALE_FACTOR });
					s.setPosition(32.0f * SCALE_FACTOR * x, 32.0f * SCALE_FACTOR * (y + 3));
					m_data->window.draw(s);
				}
			}
		}
		
		for (std::list<Snow>::iterator iterator = m_snow.begin(); iterator != m_snow.end(); iterator++)
		{
			iterator->draw();
		}
		
		m_player.draw();
		m_data->window.draw(m_scoreText);

		m_data->window.display();
		return true;
	}

	bool GameState::Pause()
	{
		s_backgroundMusic.pause();
		return true;
	}

	bool GameState::Resume()
	{
		s_backgroundMusic.play();
		return true;
	}
}