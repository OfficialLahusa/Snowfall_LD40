#pragma once

#include <SFML/Graphics.hpp>
#include "../../SimpleSfmlEngine/engine.h"

namespace sse
{
	class PauseScreen : public State
	{
	public:
		PauseScreen(GameDataRef data);

		bool Init();

		bool Terminate();

		bool HandleInput(float dt);
		bool Update(float dt);
		bool Render(float dt);

	private:
		GameDataRef m_data;

		sf::Sprite m_buttons;

		bool m_quit = false;

		sf::Image m_image;
		sf::Texture m_backGroundTexture;
		sf::Sprite m_backGround;
	};
}