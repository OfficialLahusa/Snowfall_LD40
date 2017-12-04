#pragma once

#include <SFML/Graphics.hpp>
#include "../../SimpleSfmlEngine/engine.h"

namespace sse
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, size_t score);

		bool Init();

		bool HandleInput(float dt);
		bool Update(float dt);
		bool Render(float dt);

	private:

		GameDataRef m_data;

		size_t m_score;
		sf::Text m_scoreText;
		sf::Clock m_clock;
		sf::Sprite m_background;
	};
}