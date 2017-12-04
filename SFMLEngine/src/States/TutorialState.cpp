#include <iostream>
#include "TutorialState.h"
#include "../DEFINITIONS.h"
#include "MenuState.h"

namespace sse
{
	static sf::Music s_backgroundMusic;

	TutorialState::TutorialState(GameDataRef data)
		: m_data(data)
		, m_map(NUM_TILES_X * NUM_TILES_Y)
		, m_player(data)
	{

	}

	bool TutorialState::Terminate()
	{
		s_backgroundMusic.setLoop(false);
		s_backgroundMusic.pause();
		s_backgroundMusic.stop();

		return true;
	}



	bool TutorialState::Init()
	{
		m_state = CurrentState::howToMove;

		m_hauses.setTexture(m_data->assets.GetTexture("hauses"));
		m_hauses.setScale(SCALE_FACTOR, SCALE_FACTOR);

		m_howToMove.setFillColor(sf::Color(0, 0, 0));
		m_howToPickUp.setFillColor(sf::Color(0, 0, 0));
		m_howToPutDown.setFillColor(sf::Color(0, 0, 0));
		m_secondSnowLayer.setFillColor(sf::Color(0, 0, 0));
		m_lastSnowLayer.setFillColor(sf::Color(0, 0, 0));
		m_newBucketDelivert.setFillColor(sf::Color(0, 0, 0));

		m_howToMove.setOutlineThickness(1);
		m_howToPickUp.setOutlineThickness(1);
		m_howToPutDown.setOutlineThickness(1);
		m_secondSnowLayer.setOutlineThickness(1);
		m_lastSnowLayer.setOutlineThickness(1);
		m_newBucketDelivert.setOutlineThickness(1);

		m_howToMove.setOutlineColor(sf::Color(255, 255, 255));
		m_howToPickUp.setOutlineColor(sf::Color(255, 255, 255));
		m_howToPutDown.setOutlineColor(sf::Color(255, 255, 255));
		m_secondSnowLayer.setOutlineColor(sf::Color(255, 255, 255));
		m_lastSnowLayer.setOutlineColor(sf::Color(255, 255, 255));
		m_newBucketDelivert.setOutlineColor(sf::Color(255, 255, 255));

		m_howToMove.setCharacterSize(30);
		m_howToPickUp.setCharacterSize(30);
		m_howToPutDown.setCharacterSize(26);
		m_secondSnowLayer.setCharacterSize(30);
		m_lastSnowLayer.setCharacterSize(30);
		m_newBucketDelivert.setCharacterSize(23);

		m_howToMove.setFont(m_data->assets.GetFont("tutorial_font"));
		m_howToPickUp.setFont(m_data->assets.GetFont("tutorial_font"));
		m_howToPutDown.setFont(m_data->assets.GetFont("tutorial_font"));
		m_secondSnowLayer.setFont(m_data->assets.GetFont("tutorial_font"));
		m_lastSnowLayer.setFont(m_data->assets.GetFont("tutorial_font"));
		m_newBucketDelivert.setFont(m_data->assets.GetFont("tutorial_font"));

		m_howToMove.setString("Use W, A, S, and D to\nmove to the bucket.");
		m_howToPickUp.setString("Stand near the bucket\nand left click it with the cursor\nto pick it up.");
		m_howToPutDown.setString("Now go to the shadow on the ground,\nstand next to it (make sure you don't\nstand directly on it)\nand then left click with the cursor again\n to put the bucket down and wait.");
		m_secondSnowLayer.setString("Continue filling the bucket.");
		m_lastSnowLayer.setString("Continue filling the bucket.");
		m_newBucketDelivert.setString("Now you receive a new bucket because\nthe first bucket is full.\nYou can't pick up a full bucket.\nIf you can't catch a snowflake you will lose.\nTip: You can't go through buckets so try\nto not lock yourself in. Have fun!");

		s_backgroundMusic.openFromFile(BACK_GROUND_MUSIC_FILEPATH);
		s_backgroundMusic.play();
		s_backgroundMusic.setLoop(true);
		s_backgroundMusic.setVolume(15);


		for (size_t x = 0; x < NUM_TILES_X; x++)
		{
			for (size_t y = 0; y < NUM_TILES_Y; y++)
			{
				m_map[y * NUM_TILES_X + x].shape.setTexture(m_data->assets.GetTexture("map_texture"));
				m_map[y * NUM_TILES_X + x].shape.setScale(SCALE_FACTOR, SCALE_FACTOR);
				m_map[y * NUM_TILES_X + x].shape.setPosition(32.0f * SCALE_FACTOR * x, 32.0f * SCALE_FACTOR * y + SCREEN_HEIGHT - MAP_HEIGHT);
			}
		}

		m_map[0].bucketSnow = 0;

		m_player.setSpeed(125.0f * SCALE_FACTOR);

		m_snow.emplace_back(m_data, static_cast<float>(m_rng.randomInteger<int>(0, NUM_TILES_X - 1)), 1.0f, MAP_HEIGHT * 1.0f, 75.0f * SCALE_FACTOR);
		m_snow.begin()->update(0.7f);
		m_snow.begin()->update(0.1f);
		return true;
	}

	bool TutorialState::HandleInput(float dt)
	{
		sf::Event event;
		sf::Sprite playerPosSprite;
		playerPosSprite.setTextureRect({ 0, 0, 32 * SCALE_FACTOR * 2, 32 * SCALE_FACTOR * 2 });
		playerPosSprite.setOrigin(32 * SCALE_FACTOR, 32 * SCALE_FACTOR);
		playerPosSprite.setPosition(m_player.getSprite().getPosition());

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
					m_data->machine.AddState(StateRef(new MenuState(m_data)), true);
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (m_state == CurrentState::newBucketDelivert && m_clock.getElapsedTime().asSeconds() >= 10.0f)
				{
					m_data->machine.AddState(StateRef(new MenuState(m_data)), true);
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (size_t i = 0; i < m_map.size(); i++)
					{

						if (m_player.getBucket() >= 0 && m_map[i].bucketSnow == -1 && !m_data->input.IsPointOnSprite(m_map[i].shape, { static_cast<int>(m_player.getSprite().getPosition().x), static_cast<int>(m_player.getSprite().getPosition().y) }) && m_data->input.IsPointOnSprite(m_map[i].shape, { event.mouseButton.x, event.mouseButton.y }) && Collision::CircleTest(playerPosSprite, m_map[i].shape))
						{
							for (auto it = m_snow.begin(); it != m_snow.end(); it++)
							{
								if (it->getPos().x == m_map[i].shape.getPosition().x / 32.0f / SCALE_FACTOR && it->getPos().y == m_map[i].shape.getPosition().y / 32.0f / SCALE_FACTOR - 3)
								{
									m_state = m_state == CurrentState::howToPutDown ? CurrentState::waiting : m_state;
								}
							}
						
							m_map[i].bucketSnow = m_player.getBucket();
							m_player.setSnow(-1);
						}
						else if (m_player.getBucket() == -1 && m_map[i].bucketSnow < 3 && m_data->input.IsPointOnSprite(m_map[i].shape, { event.mouseButton.x, event.mouseButton.y }) && Collision::CircleTest(playerPosSprite, m_map[i].shape))
						{
							m_state = m_state == CurrentState::howToPickUp ? CurrentState::howToPutDown : m_state;
							m_player.setSnow(m_map[i].bucketSnow);
							m_map[i].bucketSnow = -1;
						}
						else if (m_player.getBucket() == -1 && m_map[i].bucketSnow == 3)
						{
							m_map[i].bucketSnow = 4;
							m_player.setSnow(0);
						}
					}
				}

			}
		}
		if (Collision::CircleTest(playerPosSprite, m_map[0].shape))
		{
			m_state = m_state == CurrentState::howToMove ? CurrentState::howToPickUp : m_state;
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

	bool TutorialState::Update(float dt)
	{
		m_player.update(dt, m_map);

		if (m_state > CurrentState::howToPutDown && m_state < CurrentState::newBucketDelivert)
		{
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

						switch (m_state)
						{
						case sse::TutorialState::CurrentState::waiting:
							m_state = CurrentState::secondSnowLayer;
							break;
						case sse::TutorialState::CurrentState::secondSnowLayer:
							m_state = CurrentState::lastSnowLayer;
							break;
						case sse::TutorialState::CurrentState::lastSnowLayer:
							m_state = CurrentState::newBucketDelivert;
							m_clock.restart();
							break;
						default:
							break;
						}
					}

					

					m_snow.erase(it);
					m_snow.emplace_back(m_data, static_cast<float>(m_rng.randomInteger<int>(0, NUM_TILES_X - 1)), static_cast<float>(m_rng.randomInteger<int>(0, NUM_TILES_Y - 1)), static_cast<float>(m_rng.randomInteger<int>(MAP_HEIGHT * 2, MAP_HEIGHT * 3)), 35.0f * SCALE_FACTOR);
					break;
				}
				else
				{
					it->update(dt);
				}
			}
		}
	
		return true;
	}

	bool TutorialState::Render(float dt)
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

		switch (m_state)
		{
		case sse::TutorialState::CurrentState::howToMove:
			m_data->window.draw(m_howToMove);
			break;
		case sse::TutorialState::CurrentState::howToPickUp:
			m_data->window.draw(m_howToPickUp);
			break;
		case sse::TutorialState::CurrentState::howToPutDown:
			m_data->window.draw(m_howToPutDown);
			break;
		case sse::TutorialState::CurrentState::secondSnowLayer:
			m_data->window.draw(m_secondSnowLayer);
			break;
		case sse::TutorialState::CurrentState::lastSnowLayer:
			m_data->window.draw(m_lastSnowLayer);
			break;
		case sse::TutorialState::CurrentState::waiting:

				break;
		case sse::TutorialState::CurrentState::newBucketDelivert:
			m_data->window.draw(m_newBucketDelivert);
			break;
		default:
			break;
		}

		m_data->window.display();
		return true;
	}
}