#pragma once
#include "../SimpleSfmlEngine/engine.h"
#include "DEFINITIONS.h"
#include <SFML\Graphics.hpp>

namespace sse
{
	class Snow
	{
	public:
		Snow(GameDataRef data, float x, float y, float height, float fallSpeed);

		bool isDead() { return m_dead; }

		void update(float dt);

		void draw();

		sf::Vector2f getPos();

	private:
		GameDataRef m_data;
		sf::RectangleShape m_shape;
		sf::RectangleShape m_shadow;
		float m_height;
		float m_fallSpeed;
		bool m_dead = false;
		float m_tileX, m_tileY;
		float m_x, m_y;

		rng m_rng;
	};
}