#include "InputManager.h"
#include <SFML\Window.hpp>

using namespace Framework;
using namespace sf;

Framework::InputManager* Framework::InputManager::m_instance = nullptr;

InputManager* InputManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new InputManager();
	}
	return m_instance;
}

void Framework::InputManager::Init()
{
	for (int i = 0; i < Keyboard::KeyCount; ++i)
		m_engineKeysToGameKeys[i] = GameKeys::Unknown;

	m_engineKeysToMouseKeys[Mouse::Button::Left] = MouseKeys::LeftClick;
	m_engineKeysToMouseKeys[Mouse::Button::Right] = MouseKeys::RightClick;
	m_engineKeysToMouseKeys[Mouse::Button::Middle] = MouseKeys::Middle;

	m_engineKeysToGameKeys[Keyboard::Key::A] = GameKeys::KeyA;
	m_engineKeysToGameKeys[Keyboard::Key::S] = GameKeys::KeyS;
	m_engineKeysToGameKeys[Keyboard::Key::D] = GameKeys::KeyD;
	m_engineKeysToGameKeys[Keyboard::Key::W] = GameKeys::KeyW;

	for (int i = 0;i < MouseKeys::MouseKeysCount;++i)
		m_lastMouseState[i] = m_currMouseState[i] = false;

	for (int i = 0;i < GameKeys::GameKeysCount;++i)
		m_lastKeysState[i] = m_currKeysState[i] = false;
}

void Framework::InputManager::Update()
{
	for (int i = 0;i < GameKeys::GameKeysCount; ++i)
	{
		m_lastKeysState[i] = m_currKeysState[i];
	}
	for (int i = 0;i < MouseKeys::MouseKeysCount;++i)
	{
		m_lastMouseState[i] = m_currMouseState[i];
	}
}

void Framework::InputManager::ProcessEvent(const Event &currEvent)
{
	switch (currEvent.type)
	{
	case Event::KeyPressed:
		if (!(currEvent.key.code < 0 || currEvent.key.code >= Keyboard::KeyCount ||
			m_engineKeysToGameKeys[currEvent.key.code] == GameKeys::Unknown))
		{
			m_currKeysState[m_engineKeysToGameKeys[currEvent.key.code]] = true;
		}
		break;
	case Event::KeyReleased:
		if (!(currEvent.key.code < 0 || currEvent.key.code >= Keyboard::KeyCount ||
			m_engineKeysToGameKeys[currEvent.key.code] == GameKeys::Unknown))
		{
			m_currKeysState[m_engineKeysToGameKeys[currEvent.key.code]] = false;
		}
		break;
	case Event::MouseButtonPressed:
		m_currMouseState[m_engineKeysToMouseKeys[currEvent.key.code]] = true;
		break;
	case Event::MouseButtonReleased:
		m_currMouseState[m_engineKeysToMouseKeys[currEvent.key.code]] = false;
		break;
	default:
		break;
	}
}

bool Framework::InputManager::IsKeyPressed(GameKeys key)
{
	return m_currKeysState[key];
}

bool Framework::InputManager::IsKeyUp(GameKeys key)
{
	if (m_lastKeysState[key] == true && m_currKeysState[key] == false)
		return true;
	return false;
}

bool Framework::InputManager::IsKeyDown(GameKeys key)
{
	if (m_lastKeysState[key] == false && m_currKeysState[key] == true)
		return true;
	return false;
}

bool Framework::InputManager::isMousePressed(MouseKeys key)
{
	return m_currMouseState[key];
}

bool Framework::InputManager::isMouseUp(MouseKeys key)
{
	if (m_lastMouseState[key] == true && m_currMouseState[key] == false)
		return true;
	return false;
}

bool Framework::InputManager::isMouseDown(MouseKeys key)
{
	if (m_lastMouseState[key] == false && m_currMouseState[key] == true)
		return true;
	return false;
}

Vector2f Framework::InputManager::GetMousePosition(Event currEvent)
{
	return Vector2f(currEvent.mouseMove.x, currEvent.mouseMove.y);
}

Framework::InputManager::InputManager()
{
}
