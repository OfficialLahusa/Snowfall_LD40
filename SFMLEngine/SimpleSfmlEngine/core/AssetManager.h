#pragma once
#include <fstream>
#include <map>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../utils.h"

namespace sse
{
	class AssetManager
	{
	public:
		AssetManager() {}
		~AssetManager() {}


		void LoadTexture(std::string name, std::string path)
		{
			sf::Texture tex;

			if (tex.loadFromFile(path))
			{
				this->m_textures[name] = tex;
			}
			else
			{
				logger::logError("Failed to load texture!");
			}
		}
		sf::Texture &GetTexture(std::string name)
		{
			return this->m_textures[name];
		}


		void LoadFont(std::string name, std::string path)
		{
			sf::Font font;

			if (font.loadFromFile(path))
			{
				this->m_fonts[name] = font;
			}
		}
		sf::Font &GetFont(std::string name)
		{
			return this->m_fonts[name];
		}


		void LoadSoundBuffer(std::string name, std::string path)
		{
			sf::SoundBuffer soundBuffer;

			if (soundBuffer.loadFromFile(path))
			{
				this->m_soundBuffer[name] = soundBuffer;
			}
		}
		sf::SoundBuffer &GetSoundBuffer(std::string name)
		{
			return this->m_soundBuffer[name];
		}

		void LoadShaderFile(std::string name, std::string path)
		{
			std::ifstream fin(path);

			enum class ShaderType
			{
				NONE = -1, VERTEX = 0, FRAGMENT = 1
			};

			std::string line;
			std::stringstream ss[2];
			ShaderType type = ShaderType::NONE;
			while (std::getline(fin, line))
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (line.find("vertex") != std::string::npos)
					{
						type = ShaderType::VERTEX;
					}
					else if (line.find("fragment") != std::string::npos)
					{
						type = ShaderType::FRAGMENT;
					}
				}
				else if (type != ShaderType::NONE)
				{
					ss[static_cast<int>(type)] << line << '\n';
				}
			}

			m_shaders[name].loadFromMemory(ss[0].str(), ss[1].str());
		}
		sf::Shader &GetShader(std::string name)
		{
			return this->m_shaders[name];
		}
		

	private:
		std::map<std::string, sf::Texture> m_textures;
		std::map<std::string, sf::Font> m_fonts;
		std::map<std::string, sf::SoundBuffer> m_soundBuffer;
		std::map<std::string, sf::Shader> m_shaders;
	};
}