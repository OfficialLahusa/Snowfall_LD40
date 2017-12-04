#include "../SimpleSfmlEngine/engine.h"
#include "../SimpleSfmlEngine/dataTypes/hugeFloat.h"
#include "States/SplashState.h"
#include "DEFINITIONS.h"
#include <cmath>
#include <iostream>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	sse::Game(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, [](sse::GameDataRef data) { data->machine.AddState(sse::StateRef(new sse::SplashState(data))); });
	
	//std::cin.get();
	return 0;
}



// Shader sample
/*#include <SFML/Graphics.hpp>
#include <iostream>

const char VertexShader[] =
"void main()"
"{"
"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
"gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
"gl_FrontColor = gl_Color;"
"}";

const char RadialGradient[] =
"uniform vec4 color;"
"uniform vec2 center;"
"uniform float radius;"
"uniform float expand;"
"uniform float windowHeight;"
"void main(void)"
"{"
"vec2 centerFromSfml = vec2(center.x, windowHeight - center.y);"
"vec2 p = (gl_FragCoord.xy - centerFromSfml) / radius;"
"float r = sqrt(dot(p, p));"
"if (r < 1.0)"
"{"
"gl_FragColor = mix(color, gl_Color, (r - expand) / (1 - expand));"
"}"
"else"
"{"
"gl_FragColor = gl_Color;"
"}"
"}";

int main()
{
	if (!sf::Shader::isAvailable())
	{
		std::cerr << "Shaders are not available." << std::endl;
		return EXIT_FAILURE;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "Radial Gradient", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape rectangle;
	sf::Shader shader;

	rectangle.setSize({ 800, 600 });
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setOrigin(rectangle.getLocalBounds().width / 2.f, rectangle.getLocalBounds().height / 2.f);
	rectangle.setPosition(sf::Vector2f(window.getSize()) / 2.f);

	shader.loadFromMemory(VertexShader, RadialGradient);
	shader.setUniform("windowHeight", static_cast<float>(window.getSize().y)); // this must be set, but only needs to be set once (or whenever the size of the window changes)
	shader.setUniform("color", sf::Glsl::Vec4(sf::Color::White));
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();

			shader.setUniform("center", sf::Vector2f(sf::Mouse::getPosition(window)));
		}

		window.clear();
		static bool shink = false;
		static float radius = 20.0f;
		if (radius > 200.0f)
		{
			shink = true;
		}
		if (radius < 20.0f)
		{
			shink = false;
		}
		if (!shink)
		{
			radius++;
		}
		else
		{
			radius--;
		}
		shader.setUniform("radius", radius);
		shader.setUniform("expand", 0.01f);

		window.draw(rectangle, &shader);

		window.display();
	}

	return EXIT_SUCCESS;
	}*/