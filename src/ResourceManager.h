#pragma once
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	void Init();
	//void InitFromPath(std::string Path);
	sf::Texture* GetTexture(std::string TextureName); // returnez NULL daca un e
	sf::Sound* GetSound(std::string SoundName);
	sf::Font* GetFont(std::string FontName);
private:
	void DFS(std::string resourcesPath);
	std::map <std::string, sf::Texture*> m_textures;
	std::map <std::string, sf::Sound*> m_sounds; // am modificat aicilisa din Sound in SoundBuffer
	std::map <std::string, sf::Font*> m_fonts;
};

