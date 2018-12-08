#include <iostream>
#include <conio.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "InputManager.h"
#include "ResourceManager.h"

using namespace std;
using namespace sf;
using namespace Framework;

int main()
{
	
	RenderWindow window(VideoMode(600, 600), "SFML works!");

	InputManager *inputManager = InputManager::GetInstance();
	inputManager->Init();

	g_resourceManager->Init();

	Texture *texture = g_resourceManager->GetTexture("weave");
	RectangleShape player;
	player.setSize(Vector2f(200, 100));
	player.setPosition(Vector2f(150, 150));
	player.setTexture(texture);

	Font *font = g_resourceManager->GetFont("arial");
	Text text;
	text.setFont(*font);
	text.setString("Hello world!");
	text.setCharacterSize(50);
	text.setFillColor(Color::Red);
	text.setOutlineThickness(2);
	text.setOutlineColor(Color::Magenta);
	text.setPosition(Vector2f(100, 100));
	text.setRotation(45);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			inputManager->ProcessEvent(event);

			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::LControl) 
			{
				cout << "\t\t LControl was pressed\n";
			}
			if (event.type == Event::KeyPressed)
				cout << static_cast<char>(event.key.code + 65) << " key was pressed\n";
			if (event.type == Event::KeyReleased)
				cout << static_cast<char>(event.key.code + 65) << " key was released\n";
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					cout << "wheel type: vertical" << endl;
				else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
					cout << "wheel type: horizontal" << endl;
				else
					cout << "wheel type: unknown" << endl;
				/*int val = music.getVolume();
				if (event.mouseWheelScroll.delta == 1)
					music.setVolume(val + 5);
				else
					music.setVolume(val - 5);*/

				cout << "wheel movement: " << event.mouseWheelScroll.delta << endl;
				cout << "mouse x: " << event.mouseWheelScroll.x << endl;
				cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					cout << "the right button was pressed" << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					cout << "the left button was pressed" << std::endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				//sprite.setPosition(Vector2f(event.mouseMove.x, event.mouseMove.y));
				cout << "new mouse x: " << event.mouseMove.x << endl;
				cout << "new mouse y: " << event.mouseMove.y << endl;
			}
			if (event.type == sf::Event::MouseEntered)
				cout << "the mouse cursor has entered the window" << endl;

			if (event.type == sf::Event::MouseLeft)
				cout << "the mouse cursor has left the window" << endl;

		}

		if (inputManager->IsKeyPressed(KeyA))
			player.move(-0.1f, 0.0f);
		if (inputManager->IsKeyPressed(KeyD))
			player.move(0.1f, 0.0f);
		if (inputManager->IsKeyPressed(KeyW))
			player.move(0.0f, -0.1f);
		if (inputManager->IsKeyPressed(KeyS))
			player.move(0.0f, 0.1f);
		
		// updates:
		inputManager->Update();

		window.clear();
		window.draw(text);
		window.display();
	}
	return 0;
}