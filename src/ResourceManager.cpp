#include "ResourceManager.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

using namespace std;
using namespace sf;

namespace Framework
{
	ResourceManager* g_resourceManager = new ResourceManager();

	ResourceManager::ResourceManager()
	{
	}

	ResourceManager::~ResourceManager()
	{
		//stergem pointerii din memorie din mapuri
		for (map <string, Texture*> ::iterator it = m_textures.begin();it != m_textures.end();++it)
		{
			delete it->second;
		}
		for (map <string, Font*> ::iterator it = m_fonts.begin();it != m_fonts.end();++it)
		{
			delete it->second;
		}
		for (map <string, SoundBuffer*> ::iterator it = m_soundBuffers.begin();it != m_soundBuffers.end();++it)
		{
			delete it->second;
		}
	}

	void ResourceManager::Init()
	{
		//ma ocup de extensii
		//textures

		m_texturesExtensions.push_back("jpg");
		m_texturesExtensions.push_back("png");

		//fonts

		m_fontsExtensions.push_back("ttf");

		//soundBuffers

		m_soundBuffersExtensions.push_back("ogg");

		//dfs ul ala blana prin resurse cu cale relativa

		const DWORD bufferLength = MAX_PATH;
		TCHAR buffer[bufferLength];

		if (GetCurrentDirectory(bufferLength, buffer) == 0)
		{
			cout << "GetCurrentDirectory failed.";
			return;
		}
		string resourcesPath = buffer;
		resourcesPath += "\\..\\resources\\*";
		DFS(resourcesPath);
	}

	sf::Texture * ResourceManager::GetTexture(std::string textureName)
	{
		if (m_textures.find(textureName) == m_textures.end())
			return nullptr;
		return m_textures[textureName];
	}

	sf::SoundBuffer * ResourceManager::GetSoundBuffer(std::string soundName)
	{
		if (m_soundBuffers.find(soundName) == m_soundBuffers.end())
			return nullptr;
		return m_soundBuffers[soundName];
	}

	sf::Font * ResourceManager::GetFont(std::string fontName)
	{
		if (m_fonts.find(fontName) == m_fonts.end())
			return nullptr;
		return m_fonts[fontName];
	}

	void ResourceManager::DFS(string resourcesPath)
	{
		//la dfs sterg steluta si modific filtrul daca e folder(\\foldername\\*) apoi iar findfirstfile...
		WIN32_FIND_DATA file;
		HANDLE h = FindFirstFile(resourcesPath.c_str(), &file);
		BOOL findNextFileResult = 1;
		while (h != INVALID_HANDLE_VALUE && findNextFileResult != 0)
		{
			//cout << file.dwFileAttributes << " ";
			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//verific sa fie diferit de . si ..
				string cFileNameString = file.cFileName;
				if (!(cFileNameString == "." || cFileNameString == ".."))
				{
					//modific filtrul
					//cout << "directory ";
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
					{
						fileName.back() = fileName.back() - 'A' + 'a'; // tolower and toupper
					}
					extensionName.push_back(fileName.back());
					fileName.pop_back();
				}
				fileName.pop_back();
				reverse(extensionName.begin(), extensionName.end());
				// vector de extensii pentru fiecare tip de resursa si verifici acolo daca extensia e in vector vector <string> m_texturesExtensions
				if (CheckTexture(extensionName))
				{
					Texture *texture = new Texture();
					if (texture->loadFromFile(currPath))
					{
						m_textures[fileName] = texture;
						cout << "Loaded texture from: " << currPath << "\n";
					}

				}
				if (CheckFont(extensionName))
				{
					Font *font = new Font();
					if (font->loadFromFile(currPath))
					{
						m_fonts[fileName] = font;
						cout << "Loaded font from: " << currPath << "\n";
					}
				}
				if (CheckSoundBuffer(extensionName))
				{
					SoundBuffer *soundBuffer = new SoundBuffer();
					if (soundBuffer->loadFromFile(currPath))
					{
						m_soundBuffers[fileName] = soundBuffer;
						cout << "Loaded sound buffer from: " << currPath << "\n";
					}
				}
				//cout << "normal ";
			}
			//cout << file.cFileName << "\n";
			findNextFileResult = FindNextFile(h, &file);
		}
		FindClose(h);
	}

	bool Framework::ResourceManager::CheckTexture(const string & extensionName)
	{
		for (vector <string> ::iterator it = m_texturesExtensions.begin();it != m_texturesExtensions.end();++it)
			if (extensionName == (*it))
				return true;
		return false;
	}

	bool Framework::ResourceManager::CheckFont(const std::string & extensionName)
	{
		for (vector <string> ::iterator it = m_fontsExtensions.begin();it != m_fontsExtensions.end();++it)
			if (extensionName == (*it))
				return true;
		return false;
	}

	bool Framework::ResourceManager::CheckSoundBuffer(const std::string & extensionName)
	{
		for (vector <string> ::iterator it = m_soundBuffersExtensions.begin();it != m_soundBuffersExtensions.end();++it)
			if (extensionName == (*it))
				return true;
		return false;
	}
}