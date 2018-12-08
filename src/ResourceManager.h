#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Framework
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
		void Init();
		//void InitFromPath(std::string Path);
		sf::Texture* GetTexture(std::string textureName); // returnez NULL daca un e
		sf::SoundBuffer* GetSoundBuffer(std::string soundName);
		sf::Font* GetFont(std::string fontName);
	private:
		void DFS(std::string resourcesPath);
		bool CheckTexture(const std::string &extensionName);
		bool CheckFont(const std::string &extensionName);
		bool CheckSoundBuffer(const std::string &extensionName);
		std::map <std::string, sf::Texture*>		m_textures;
		std::map <std::string, sf::SoundBuffer*>	m_soundBuffers;
		std::map <std::string, sf::Font*>			m_fonts;
		std::vector <std::string>					m_texturesExtensions;
		std::vector <std::string>					m_fontsExtensions;
		std::vector <std::string>					m_soundBuffersExtensions;
	};

	extern ResourceManager* g_resourceManager;
}