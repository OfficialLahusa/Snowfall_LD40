#include "Player.h"

sse::Player::Player(GameDataRef data)
	: m_data(data)
{
	m_speed = 0.0f;

	m_pos = { MAP_WIDTH / 2, MAP_HEIGHT / 2 + SCREEN_HEIGHT - MAP_HEIGHT };

	m_player.setTexture(m_data->assets.GetTexture("player_static"));
	m_player.setScale(SCALE_FACTOR, SCALE_FACTOR);
	m_player.setOrigin(32 / 2, 32 * 2 - 6);
	m_player.setPosition(m_pos);
	

	m_bucketSnow = -1;
}

void sse::Player::update(float dt, const std::vector<mapTile>& map)
{
	switch (m_bucketSnow)
	{
	case 0:
	{
		m_player.setTexture(m_data->assets.GetTexture("player_static_empty"));
	}
	break;

	case 1:
	{
		m_player.setTexture(m_data->assets.GetTexture("player_static_slightly_full"));
	}
	break;

	case 2:
	{
		m_player.setTexture(m_data->assets.GetTexture("player_static_half_full"));
	}
	break;

	case 3:
	{
		logger::logError("Some Thing Failed");
	}
	break;

	default:
	{
		m_player.setTexture(m_data->assets.GetTexture("player_static"));
	}
	break;
	}
	sf::Vector2f newPos = m_pos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		newPos.y -= m_speed * dt;

		if (newPos.y < SCREEN_HEIGHT - MAP_HEIGHT)
		{
			newPos.y = m_pos.y;
		}
		else
		{
			for (size_t i = 0; i < map.size(); i++)
			{
				if (map[i].bucketSnow >= 0 && m_data->input.IsPointOnSprite(map[i].shape, { static_cast<int>(newPos.x), static_cast<int>(newPos.y) }))
				{
					newPos.y = m_pos.y;
					break;
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		newPos.y += m_speed * dt;

		if (newPos.y > SCREEN_HEIGHT)
		{
			newPos.y = m_pos.y;
		}
		else
		{
			for (size_t i = 0; i < map.size(); i++)
			{
				if (map[i].bucketSnow >= 0 && m_data->input.IsPointOnSprite(map[i].shape, { static_cast<int>(newPos.x), static_cast<int>(newPos.y) }))
				{
					newPos.y = m_pos.y;
					break;
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		newPos.x -= m_speed * dt;

		if (newPos.x < 0)
		{
			newPos.x = m_pos.x;
		}
		else
		{
			for (size_t i = 0; i < map.size(); i++)
			{
				if (map[i].bucketSnow >= 0 && m_data->input.IsPointOnSprite(map[i].shape, { static_cast<int>(newPos.x), static_cast<int>(newPos.y) }))
				{
					newPos.x = m_pos.x;
					break;
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		newPos.x += m_speed * dt;

		if (newPos.x > MAP_WIDTH)
		{
			newPos.x = m_pos.x;
		}
		else
		{
			for (size_t i = 0; i < map.size(); i++)
			{
				if (map[i].bucketSnow >= 0 && m_data->input.IsPointOnSprite(map[i].shape, { static_cast<int>(newPos.x), static_cast<int>(newPos.y) }))
				{
					newPos.x = m_pos.x;
					break;
				}
			}
		}
	}

	m_pos = newPos;

	m_player.setPosition(m_pos);
}


void sse::Player::draw()
{
	m_data->window.draw(m_player);
}
