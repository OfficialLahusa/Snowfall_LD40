#pragma once

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace sse
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(unsigned int width, unsigned int height, std::string title, std::function<void(GameDataRef data)> runState)
		{
			this->m_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
			this->m_data->window.setVerticalSyncEnabled(true);

			runState(this->m_data);

			this->Run();
		}

	private:
		sf::Clock m_clock;

		GameDataRef m_data = std::make_shared<GameData>();

		void Run()
		{

			while (this->m_data->window.isOpen())
			{
				if (!this->m_data->machine.ProcessStateChanges()) { return; }
				float dt = m_clock.restart().asSeconds();
				
				//TODO: handle return type
				if (!this->m_data->machine.GetActiveState()->HandleInput(dt)) { return; }
				if (!this->m_data->machine.GetActiveState()->Update(dt)) { return; }

				if (!this->m_data->machine.GetActiveState()->Render(dt)) { return; }

			}
		}
	};
}
