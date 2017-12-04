#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "../../SimpleSfmlEngine/engine.h"
#include "../Player.h"
#include "../Snow.h"


namespace sse
{


	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		bool Terminate();

		bool Init();

		bool HandleInput(float dt);
		bool Update(float dt);
		bool Render(float dt);

		bool Pause();
		bool Resume();
	private:
		GameDataRef m_data;

		std::vector<mapTile> m_map;

		std::list<Snow> m_snow;
		sf::Sprite m_hauses;

		size_t m_score = 0;
		sf::Text m_scoreText;
		rng m_rng;

		Player m_player;
	};
}