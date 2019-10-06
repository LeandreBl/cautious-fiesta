#include "CharacterCreator.hpp"

namespace cf {

    void CharacterCreation::start(sfs::Scene &scene) noexcept
	{
		scene.subscribe(*this, sf::Event::KeyPressed);
		_boxName = &addChild<sfs::InputBox>(scene, *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
	                                    sf::Vector2f(0, 0), "< new >", sf::Color::White, 20);
		_boxName->addComponent<PadderH<sfs::InputBox>>(56, *_boxName);
		_boxName->addComponent<PadderW<sfs::InputBox>>(180, *_boxName);
		for (int i = 0; i < 5; ++i) {
			auto inputBox = &addChild<sfs::CustomBox>(scene, *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
				                                      sf::Vector2f(0, 0), "< ? >", sf::Color::White, 18, "0123456789");
			inputBox->addComponent<PadderH<sfs::CustomBox>>(23 + i * 18, *inputBox);
			inputBox->addComponent<PadderL<sfs::CustomBox>>(910, *inputBox);
			_stats.emplace_back(inputBox);
		}
		_printTotal = &addChild<CharacterStatName>(scene, *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
			                                       "total", sf::Vector2f(990, 555));
	}

    void CharacterCreation::update(sfs::Scene &) noexcept
	{
		float total = 100;
		for (auto &i : _stats) {
			if (i->string() != "") {
				float value = std::atoi(i->string().c_str());
				if ((total - value) < 0) {
				    i->string(std::to_string((int)(value + (total - value))));
				    total = 0;
			    } else
				    total -= value;
			}
		 }
	    _total = total;
	    _printTotal->setString("total\n " + std::to_string((int)_total));
	}

    void CharacterCreation::onEvent(sfs::Scene &, const sf::Event &event) noexcept
	{
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Down
			    || event.key.code == sf::Keyboard::Tab)
				for (int i = 0; i < 5; i += 1) {
					if (_stats[i]->getSelected() == true) {
						_stats[i]->toggle(false);
						if (i < 4)
							_stats[i + 1]->toggle(true);
						else
							_stats[0]->toggle(true);
						break;
					}
				}
			if (event.key.code == sf::Keyboard::Up)
				for (int i = 0; i < 5; i += 1) {
					if (_stats[i]->getSelected() == true) {
						_stats[i]->toggle(false);
						if (i > 0)
							_stats[i - 1]->toggle(
								true);
						else
							_stats[4]->toggle(true);
						break;
					}
				}
		}	
	}
    Character CharacterCreation::createCharacter() noexcept {
		int s[5];
		for (size_t i = 0; i < _stats.size(); ++i)
			s[i] = std::atoi(_stats[i]->string().c_str());
		struct Character::stats stat;
		stat.life = s[0];
		stat.speed = s[1];
		stat.attack = s[2];
		stat.attackSpeed = s[3];
		stat.armor = s[4];
		std::string name = _boxName->string();
		if (name != "") {
			Character newCharacter(name, stat);
			return newCharacter;
		}
		//TODO popup
		Character newCharacter("noName", stat);
		return newCharacter;
	};
}