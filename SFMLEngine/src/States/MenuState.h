#pragma once

#include <SFML/Graphics.hpp>
#include "../../SimpleSfmlEngine/engine.h"

namespace sse
{
	class MenuState : public State
	{
	public:
		MenuState(GameDataRef data);

		bool Init();

		bool HandleInput(float dt);
		bool Update(float dt);
		bool Render(float dt);

	private:
		GameDataRef m_data;

		sf::Sprite m_backGround;
	};
}