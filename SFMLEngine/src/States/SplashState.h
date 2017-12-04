#pragma once

#include <SFML/Graphics.hpp>
#include "../../SimpleSfmlEngine/engine.h"

namespace sse
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);

		bool Init();

		bool HandleInput(float dt);
		bool Update(float dt);
		bool Render(float dt);

	private:
		float m_pixel_threshold;

		GameDataRef m_data;
		sf::Clock m_clock;
		sf::Sprite m_background;
	};
}