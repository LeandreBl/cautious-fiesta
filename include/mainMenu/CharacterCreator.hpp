#pragma once

#include <vector>

#include <InputBox.hpp>
#include <Hnavbar.hpp>

#include "Utils.hpp"
#include "GameManager.hpp"

namespace cf {
class CharacterCreation : public sfs::UI {
      public:
	CharacterCreation() noexcept
		: _boxName(nullptr)
		, _printTotal(nullptr)
		, _gameMananger(nullptr)
		, _hat(nullptr){};
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;
	void onEvent(sfs::Scene &, const sf::Event &event) noexcept;
	Character createCharacter() noexcept;

      protected:
	sfs::InputBox *_boxName;
	std::vector<sfs::CustomBox *> _stats;
	Text *_printTotal;
	float _total = 100;
	GameManager *_gameMananger;
	sfs::Sprite *_hat;
	std::vector<sfs::Hnavbar *> _hatColors;
	std::vector<int> _colors = {0, 0, 0};
};
} // namespace cf