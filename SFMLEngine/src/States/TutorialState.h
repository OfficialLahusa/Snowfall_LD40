#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "../../SimpleSfmlEngine/engine.h"
#include "../Player.h"
#include "../Snow.h"


namespace sse
{


	class TutorialState : public State
	{
	public:
		TutorialState(GameDataRef data);
		bool Terminate();

		bool Init();

		bool HandleInput(float dt);
		bool Update(float dt);
		bool Render(float dt);

	private:
		GameDataRef m_data;

		std::vector<mapTile> m_map;

		std::list<Snow> m_snow;
		sf::Sprite m_hauses;


		sf::Text m_howToMove;
		sf::Text m_howToPickUp;
		sf::Text m_howToPutDown;
		sf::Text m_secondSnowLayer;
		sf::Text m_lastSnowLayer;
		sf::Text m_newBucketDelivert;
		sf::Clock m_clock;
		enum class CurrentState : short
		{
			howToMove = 0,
			howToPickUp = 1,
			howToPutDown = 2,
			waiting = 3,
			secondSnowLayer = 4,
			lastSnowLayer = 5,
			newBucketDelivert = 6
		};

		CurrentState m_state;
		rng m_rng;

		Player m_player;
	};
}