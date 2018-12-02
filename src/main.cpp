#include <iostream>
#include <conio.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "InputManager.h"

using namespace std;
using namespace sf;
using namespace Framework;

int main()
{
	RenderWindow window(VideoMode(600, 600), "SFML works!");
	Font font;
	if (!font.loadFromFile("../resources/arial.ttf"))
		return 0;
	Texture texture;
	//ResourceManager::GetInstance()->GetTexture("texture1");
	/*
	resources/textures/level1/texture1
	resources/textures/level2/texture1
	resources/textures/names.txt
		level1/texture1 texturaMea
		level2/texture1 texturaTa
	*/
	if (!texture.loadFromFile("../resources/texture1.JPG"))
		return 0;
	Music music;
	if (!music.openFromFile("../resources/music.ogg"))
		return 0;
	//music.play();
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 200, 200));
	sprite.setOrigin(100, 100);	
	Text text;
	text.setFont(font);
	text.setString("Hello world!");
	text.setCharacterSize(50);
	text.setFillColor(Color::Red);
	text.setOutlineThickness(2);
	text.setOutlineColor(Color::Magenta);
	text.setPosition(Vector2f(100, 100));
	text.setRotation(45);
	CircleShape circle;
	circle.setFillColor(Color::Cyan);
	circle.setRadius(100);
	circle.setPosition(Vector2f(50, 50));
	circle.setTexture(&texture);
	RectangleShape player;
	player.setSize(Vector2f(200, 100));
	player.setPosition(Vector2f(150, 150));
	player.setTexture(&texture);
	ConvexShape convex;
	convex.setPointCount(5);
	convex.setFillColor(Color::Cyan);
	convex.setPosition(Vector2f(100, 100));
	convex.setPoint(0, sf::Vector2f(0.f, 0.f));
	convex.setPoint(1, sf::Vector2f(150.f, 10.f));
	convex.setPoint(2, sf::Vector2f(120.f, 90.f));
	convex.setPoint(3, sf::Vector2f(30.f, 100.f));
	convex.setPoint(4, sf::Vector2f(0.f, 50.f));
	InputManager *inputManager = InputManager::GetInstance();
	inputManager->Init();
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
				int val = music.getVolume();
				if (event.mouseWheelScroll.delta == 1)
					music.setVolume(val + 5);
				else
					music.setVolume(val - 5);

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
			cout << "!!!!!! 1\n";
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
			cout << "!!!!!! 2\n";


		if (inputManager->IsKeyPressed(KeyA))
			player.move(-0.1f, 0.0f);
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
			player.move(0.1f, 0.0f);
		if (Keyboard::isKeyPressed(Keyboard::Key::W))
			player.move(0.0f, -0.1f);
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
			player.move(0.0f, 0.1f);
		
		// updates:
		inputManager->Update();

		window.clear();
		window.draw(player);
		window.display();
	}
	music.stop();
	return 0;
}