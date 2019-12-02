#include "InputHandler.hpp"
#include "Udp.hpp"

namespace cf
{

void InputHandler::start(sfs::Scene &scene) noexcept
{
	_gameManager = scene.getGameObjects<GameManager>()[0];
	scene.subscribe(*this, sf::Event::KeyPressed);
	scene.subscribe(*this, sf::Event::KeyReleased);
	scene.subscribe(*this, sf::Event::MouseButtonPressed);
	scene.subscribe(*this, sf::Event::MouseButtonReleased);
	scene.subscribe(*this, sf::Event::LostFocus);
	setDefaultKeys();
	resetFocus();
}

void InputHandler::resetFocus() noexcept
{
	_keyStates[UdpPrctl::inputType::UP] = UdpPrctl::inputAction::RELEASED;
	_keyStates[UdpPrctl::inputType::DOWN] = UdpPrctl::inputAction::RELEASED;
	_keyStates[UdpPrctl::inputType::LEFT] = UdpPrctl::inputAction::RELEASED;
	_keyStates[UdpPrctl::inputType::RIGHT] = UdpPrctl::inputAction::RELEASED;
	_keyStates[UdpPrctl::inputType::ATTACK1] = UdpPrctl::inputAction::RELEASED;
	_keyStates[UdpPrctl::inputType::ATTACK2] = UdpPrctl::inputAction::RELEASED;
}

void InputHandler::onEvent(sfs::Scene &, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::LostFocus)
	{
		resetFocus();
		return;
	}
	if (_optionIsActive == false && _gameIsStarted == true)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			const auto k = UdpPrctl::inputAction::PRESSED;
			const auto type = getEvtKey(event.type, event.key.code);
			const auto kp = _keyStates[type];
			if (type == UdpPrctl::inputType::UNKNOWN_KEY || k == kp)
				return;
			else if (kp == UdpPrctl::inputAction::RELEASED)
			{
				_gameManager->_udp->sendInput(k, type);
			}
			_keyStates[type] = k;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			const auto k = UdpPrctl::inputAction::RELEASED;
			const auto type = getEvtKey(event.type, event.key.code);
			const auto kp = _keyStates[type];
			if (type == UdpPrctl::inputType::UNKNOWN_KEY || k == kp)
				return;
			else if (kp == UdpPrctl::inputAction::PRESSED)
			{
				_gameManager->_udp->sendInput(k, type);
			}
			_keyStates[type] = k;
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			const auto k = UdpPrctl::inputAction::PRESSED;
			const auto type = getEvtKey(event.type, event.mouseButton.button);
			if (type == UdpPrctl::inputType::UNKNOWN_KEY)
				return;
			const auto kp = _keyStates[type];
			_gameManager->_udp->sendInput(k, type);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			const auto k = UdpPrctl::inputAction::RELEASED;
			const auto type = getEvtKey(event.type, event.mouseButton.button);
			if (type == UdpPrctl::inputType::UNKNOWN_KEY)
				return;
			const auto kp = _keyStates[type];
			_gameManager->_udp->sendInput(k, type);
		}
	}
	else if (_optionIsActive == true && _changeKeys == true)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			setEvtKey(sf::Event::KeyPressed, event.key.code, _tmpType);
			setEvtKey(sf::Event::KeyReleased, event.key.code, _tmpType);
			_tmpType = UdpPrctl::inputType::UNKNOWN_KEY;
			_changeKeys = false;
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			setEvtKey(sf::Event::MouseButtonPressed, event.mouseButton.button,
					  _tmpType);
			setEvtKey(sf::Event::MouseButtonReleased, event.mouseButton.button,
					  _tmpType);
			_tmpType = UdpPrctl::inputType::UNKNOWN_KEY;
			_changeKeys = false;
		}
	}
}

void InputHandler::setDefaultKeys() noexcept
{
	std::vector<std::vector<enum UdpPrctl::inputType>> newMatrix;
	_evtsMatrix = newMatrix;

	setEvtKey(sf::Event::EventType::KeyPressed, sf::Keyboard::Q, UdpPrctl::inputType::LEFT);
	setEvtKey(sf::Event::EventType::KeyReleased, sf::Keyboard::Q, UdpPrctl::inputType::LEFT);
	setEvtKey(sf::Event::EventType::KeyPressed, sf::Keyboard::D, UdpPrctl::inputType::RIGHT);
	setEvtKey(sf::Event::EventType::KeyReleased, sf::Keyboard::D, UdpPrctl::inputType::RIGHT);
	setEvtKey(sf::Event::EventType::KeyPressed, sf::Keyboard::Z, UdpPrctl::inputType::UP);
	setEvtKey(sf::Event::EventType::KeyReleased, sf::Keyboard::Z, UdpPrctl::inputType::UP);
	setEvtKey(sf::Event::EventType::KeyPressed, sf::Keyboard::S, UdpPrctl::inputType::DOWN);
	setEvtKey(sf::Event::EventType::KeyReleased, sf::Keyboard::S, UdpPrctl::inputType::DOWN);
	setEvtKey(sf::Event::EventType::MouseButtonPressed, sf::Mouse::Button::Left,
			  UdpPrctl::inputType::ATTACK1);
	setEvtKey(sf::Event::EventType::MouseButtonReleased, sf::Mouse::Button::Left,
			  UdpPrctl::inputType::ATTACK1);
	setEvtKey(sf::Event::EventType::MouseButtonPressed, sf::Mouse::Button::Right,
			  UdpPrctl::inputType::ATTACK2);
	setEvtKey(sf::Event::EventType::MouseButtonReleased, sf::Mouse::Button::Right,
			  UdpPrctl::inputType::ATTACK2);
}

void InputHandler::setEvtKey(sf::Event::EventType type, int key,
							 enum UdpPrctl::inputType value) noexcept
{
	if (type >= _evtsMatrix.size())
		_evtsMatrix.resize(type + 1);
	if (key >= (int)_evtsMatrix[type].size())
		_evtsMatrix[type].resize(key + 1, UdpPrctl::inputType::UNKNOWN_KEY);
	if (type == sf::Event::EventType::MouseButtonPressed)
	{
		_evtsMatrix[sf::Event::EventType::KeyPressed].resize(
			103, UdpPrctl::inputType::UNKNOWN_KEY);
		if (key == 0)
			_evtsMatrix[sf::Event::EventType::KeyPressed][101] = value;
		else if (key == 1)
			_evtsMatrix[sf::Event::EventType::KeyPressed][102] = value;
	}
	_evtsMatrix[type][key] = value;
}

enum UdpPrctl::inputType InputHandler::getEvtKey(sf::Event::EventType type, int key) noexcept
{
	if (type >= _evtsMatrix.size() || key >= (int)_evtsMatrix[type].size())
		return UdpPrctl::inputType::UNKNOWN_KEY;
	return _evtsMatrix[type][key];
}

void InputHandler::changeKeys(bool mode, UdpPrctl::inputType type) noexcept
{
	_changeKeys = mode;
	_tmpType = type;
	for (auto &i : _evtsMatrix)
	{
		for (auto &j : i)
			if (j == _tmpType)
				j = UdpPrctl::inputType::UNKNOWN_KEY;
	}
}

} // namespace cf