#include "Snow.h"

namespace sse
{
	Snow::Snow(GameDataRef data, float x, float y, float height, float fallSpeed)
		: m_data(data)
	{

		m_tileX = x;
		m_tileY = y;

		m_x = x * 32 * SCALE_FACTOR + 32 * SCALE_FACTOR / 2;
		m_y = (y+3) * 32 * SCALE_FACTOR + 32 * SCALE_FACTOR / 3;
		m_height = height;
		m_fallSpeed = fallSpeed;

		m_shadow.setTexture(&m_data->assets.GetTexture("shadow"));
		m_shadow.setSize({ 8 * SCALE_FACTOR, 8 * SCALE_FACTOR });
		m_shadow.setScale(1.5f, 1.5f);
		m_shadow.setOrigin(4 * SCALE_FACTOR, 4 * SCALE_FACTOR);
		m_shadow.setPosition(m_x, m_y);
		m_shadow.setFillColor(sf::Color(0, 0, 0, static_cast<int>(std::fabs((-(m_shape.getPosition().y - m_y) / m_height * 255) - 256))));

		m_shape.setTexture(&m_data->assets.GetTexture("flacke"));
		m_shape.setSize({ 8 * SCALE_FACTOR, 8 * SCALE_FACTOR });
		m_shape.setOrigin(4 * SCALE_FACTOR, 4 * SCALE_FACTOR);
		m_shape.setPosition(m_x, m_y - height);
	}

	void Snow::update(float dt)
	{
		
		m_shadow.setFillColor(sf::Color(0, 0, 0, 1 + static_cast<int>(std::fabs((-(m_shape.getPosition().y - m_y) / m_height * 255)- 256))));

		m_shape.move(0, m_fallSpeed * dt);
		m_shape.rotate((m_rng.randomInteger<int>(100, 150) * (m_rng.randomInteger<int>(0, 1) == 0 ? 1.0f : -1.0f)) * dt);
		if (m_shape.getPosition().y >= m_y)
		{
			m_shape.setPosition(m_x, m_y);
			m_dead = true;
		}
	}

	void Snow::draw()
	{
		m_data->window.draw(m_shadow);
		m_data->window.draw(m_shape);
	}
	sf::Vector2f Snow::getPos()
	{
		return { m_tileX, m_tileY };
	}
}