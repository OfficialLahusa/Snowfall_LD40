#pragma once
#include "../SimpleSfmlEngine/engine.h"
#include "DEFINITIONS.h"
#include <SFML\Graphics.hpp>
#include "Snow.h"
#include <vector>

namespace sse
{

	struct mapTile
	{
		short bucketSnow = -1;// -1 == noBucket
		sf::Sprite shape;
	};

	class Player
	{
	public:
		Player(GameDataRef data);

		void update(float dt, const std::vector<mapTile> &map);

		void draw();

		void setSpeed(float speed) { m_speed = speed; }

		const sf::Sprite &getSprite() { return m_player; }

		short getBucket() { return m_bucketSnow; }
		void setSnow(short val) { m_bucketSnow = val; }
	private:
		GameDataRef m_data;
		sf::Vector2f m_pos;

		short m_bucketSnow = -1;
		float m_speed;
		sf::Sprite m_player;
	};

}