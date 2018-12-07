#include "ResourceManager.h"
#include <Windows.h>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

using namespace std;
using namespace sf;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Init()
{
	string resourcesPath = "E:\\INFO\\Programming\\Mircea_pregatire\\snake\\resources\\*";
	DFS(resourcesPath);
}

sf::Texture * ResourceManager::GetTexture(std::string TextureName)
{
	if (m_textures.find(TextureName) == m_textures.end())
		return nullptr;
	return m_textures[TextureName];
}

sf::Sound * ResourceManager::GetSound(std::string SoundName)
{
	if (m_sounds.find(SoundName) == m_sounds.end())
		return nullptr;
	return m_sounds[SoundName];
}

sf::Font * ResourceManager::GetFont(std::string FontName)
{
	if (m_fonts.find(FontName) == m_fonts.end())
		return nullptr;
	return m_fonts[FontName];
}

void ResourceManager::DFS(string resourcesPath)
{
	//la dfs sterg steluta si modific filtrul daca e folder(\\foldername\\*) apoi iar findfirstfile...
	WIN32_FIND_DATA file;
	HANDLE h = FindFirstFile(resourcesPath.c_str(), &file);
	BOOL findNextFileResult = 1;
	while (h != INVALID_HANDLE_VALUE && findNextFileResult != 0)
	{
		cout << file.dwFileAttributes << " ";
		if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//verific sa fie diferit de . si ..
			if (!(file.cFileName[0] == '.' || (file.cFileName[0] == '.' && file.cFileName[1] == '.')))
			{
				//modific filtrul
				cout << "directory ";
				string nextPath = resourcesPath;
				nextPath.pop_back();
				nextPath += file.cFileName;
				nextPath += "\\*";
				DFS(nextPath);
			}
		}
		else // verific extensia
		{
			//pun in map pointer ul la numele fisierului
			string fileName = file.cFileName;
			string currPath = resourcesPath;
			currPath.pop_back();
			currPath += fileName;
			string extensionName = "";
			while (fileName.back() != '.')
			{
				if ('A' <= fileName.back() && fileName.back() <= 'Z')
					fileName.back() = fileName.back() ^ 'A' ^ 'a';
				extensionName.push_back(fileName.back());
				fileName.pop_back();
			}
			fileName.pop_back();
			reverse(extensionName.begin(), extensionName.end());
			if (extensionName == "jpg" || extensionName == "png")
			{
				Texture *texture = new Texture();
				if (texture->loadFromFile(currPath))
					m_textures[fileName] = texture;
			}
			if (extensionName == "ttf")
			{
				Font *font = new Font();
				if (font->loadFromFile(currPath))
					m_fonts[fileName] = font;
			}
			if (extensionName == "ogg")
			{
				SoundBuffer soundBuffer;
				if (soundBuffer.loadFromFile(currPath))
				{
					Sound *sound = new Sound();
					sound->setBuffer(soundBuffer);
					m_sounds[fileName] = sound;
				}
			}
			cout << "normal ";
		}
		//cout << file.cFileName << "\n";
		findNextFileResult = FindNextFile(h, &file);
	}
	FindClose(h);
}
