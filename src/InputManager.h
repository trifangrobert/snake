#pragma once
#include <SFML/Window.hpp>

namespace Framework 
{
	enum GameKeys
	{
		Unknown = -1,
		KeyA = 0,
		KeyS,
		KeyD,
		KeyW,

		GameKeysCount
	};
	enum MouseKeys
	{
		LeftClick = 0, 
		RightClick, 
		Middle, 

		MouseKeysCount
	};
	class InputManager
	{
	public:
		static InputManager* GetInstance();
		/*
		init: initializez cei doi vectori lastState, currState
		update: lastState devine currState, currState devine iar 0 peste tot;
		process event iei event.key.code e de tipul Keyboard::Key::A -- currState il actualizez cu eventurile
		mouseposition
		isKeyDown
		isKeyUp
		isKeyPressed
		si pentru mouse...
		*/
		void Init();
		void Update();
		void ProcessEvent(const sf::Event &currEvent);
		bool IsKeyPressed(GameKeys key);
		bool IsKeyUp(GameKeys key);
		bool IsKeyDown(GameKeys key);
		bool isMousePressed(MouseKeys key);
		bool isMouseUp(MouseKeys key);
		bool isMouseDown(MouseKeys key);
		sf::Vector2f GetMousePosition(sf::Event currEvent);

	private:
		GameKeys m_engineKeysToGameKeys[sf::Keyboard::Key::KeyCount];
		MouseKeys m_engineKeysToMouseKeys[sf::Mouse::Button::ButtonCount];

		InputManager();
		static InputManager* m_instance;
		bool m_lastKeysState[GameKeys::GameKeysCount], m_currKeysState[GameKeys::GameKeysCount];
		bool m_lastMouseState[MouseKeys::MouseKeysCount], m_currMouseState[MouseKeys::MouseKeysCount];
	};
}