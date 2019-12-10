#pragma once

#include "GameManager.hpp"

namespace cf {
class InputHandler : public sfs::GameObject {
      public:
	InputHandler(GameManager &manager) noexcept;
	void start(sfs::Scene &scene) noexcept;
	void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;
	void setDefaultKeys() noexcept;
	void setEvtKey(const sf::Event::EventType type, int key,
		       enum UdpPrctl::inputType value) noexcept;
	void changeKeys(bool mode, UdpPrctl::inputType type) noexcept;
	void changeGameStarted(bool mode) noexcept
	{
		_gameIsStarted = mode;
	};
	void changeOption(bool mode) noexcept
	{
		_optionIsActive = mode;
	};
	bool getChangeKeys() noexcept
	{
		return _changeKeys;
	};
	enum UdpPrctl::inputType getEvtKey(sf::Event::EventType type, int key) noexcept;
	std::vector<std::vector<enum UdpPrctl::inputType>> getMatrix() noexcept
	{
		return _evtsMatrix;
	};

      protected:
	void resetFocus() noexcept;
	GameManager &_manager;
	std::vector<std::vector<enum UdpPrctl::inputType>> _evtsMatrix;
	std::unordered_map<UdpPrctl::inputType, UdpPrctl::inputAction> _keyStates;
	UdpPrctl::inputType _tmpType;
	sf::Vector2f _prevMove;
	bool _optionIsActive = false;
	bool _changeKeys = false;
	bool _gameIsStarted = false;
};
} // namespace cf