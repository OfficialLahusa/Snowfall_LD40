#pragma once

#include <SFML/Graphics.hpp>

namespace sse
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool IsPointOnSprite(sf::Sprite object, sf::Vector2i point)
		{
			sf::IntRect tempRect(static_cast<int>(object.getPosition().x), static_cast<int>(object.getPosition().y), static_cast<int>(object.getGlobalBounds().width), static_cast<int>(object.getGlobalBounds().height));
			if (tempRect.contains(point))
			{
					return true;
			}
			return false;
		}

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, const sf::RenderWindow &window)
		{
			if (sf::Mouse::isButtonPressed(button))
			{
				sf::IntRect tempRect(static_cast<int>(object.getPosition().x), static_cast<int>(object.getPosition().y), static_cast<int>(object.getGlobalBounds().width), static_cast<int>(object.getGlobalBounds().height));
				if (tempRect.contains(sf::Mouse::getPosition(window)))
				{
					return true;
				}

			}
			return false;
		}

		bool IsCursorOnSprite(sf::Sprite object, const sf::RenderWindow &window)
		{
			sf::IntRect tempRect(static_cast<int>(object.getPosition().x), static_cast<int>(object.getPosition().y), static_cast<int>(object.getGlobalBounds().width), static_cast<int>(object.getGlobalBounds().height));
			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
			return false;
		}

		sf::Vector2i GetCursorPosition(sf::RenderWindow &window)
		{
			return sf::Mouse::getPosition();
		}

	private:

	};


}
