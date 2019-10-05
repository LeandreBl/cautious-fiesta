#pragma once

#include <iostream>
#include <vector>
#include <GameObject.hpp>
#include <Hnavbar.hpp>
#include <InputBox.hpp>
#include "Serializer.hpp"
#include "PaddedSprite.hpp"

namespace cf
{
class Character
{
      public:
	struct stats {
		float life;
		float speed;
		float attack;
		float attackSpeed;
		float armor;
	};
	Character(const std::string &name, const struct stats &stats) noexcept
	    : _name(name), _stats(stats){};
	void setName(const std::string &name) noexcept
	{
		_name = name;
	};
	std::string getName() const noexcept
	{
		return _name;
	};
	void setStats(const struct stats &stats) noexcept
	{
		_stats = stats;
	};
	const struct stats &getStats() const noexcept
	{
		return _stats;
	};
	void setLife(float life) noexcept
	{
		_stats.life = life;
	};
	float getLife() const noexcept
	{
		return _stats.life;
	};
	void setSpeed(float speed) noexcept
	{
		_stats.speed = speed;
	};
	float getSpeed() const noexcept
	{
		return _stats.speed;
	};
	void setAttack(float attack) noexcept
	{
		_stats.attack = attack;
	};
	float getAttack() const noexcept
	{
		return _stats.attack;
	};
	void setAttackSpeed(float as) noexcept
	{
		_stats.attackSpeed = as;
	};
	float getAttackSpeed() const noexcept
	{
		return _stats.attackSpeed;
	};
	void setArmor(float armor) noexcept
	{
		_stats.armor = armor;
	};
	float getArmor() const noexcept
	{
		return _stats.armor;
	};

      protected:
	std::string _name;
	struct stats _stats;
};

class CharacterStatName : public sfs::GameObject
{
      public:
	CharacterStatName(const sf::Font &font, const std::string &name,
			  const sf::Vector2f &pos) noexcept
	    : _text(nullptr)
	{
		setPosition(pos);
		_text = &addComponent<sfs::Text>(font, name, sf::Color::White,
						 18);
	}
	void setString(const std::string &str) noexcept
	{
		_text->setString(str);
	}

      protected:
	sfs::Text *_text;
};

class CharacterCreation : public sfs::UI
{
      public:
	CharacterCreation() noexcept : _box(nullptr), _printTotal(nullptr){};
	void start(sfs::Scene &scene) noexcept
	{
		scene.subscribe(*this, sf::Event::KeyPressed);
		_box = &addChild<sfs::InputBox>(
			scene,
			*scene.getAssetFont("assets/fonts/commodore-64.ttf"),
			sf::Vector2f(0, 0), "< new >", sf::Color::White, 20);
		_box->addComponent<PadderH<sfs::InputBox>>(56, *_box);
		_box->addComponent<PadderW<sfs::InputBox>>(180, *_box);
		for (int i = 0; i < 5; ++i) {
			auto inputBox = &addChild<sfs::CustomBox>(
				scene,
				*scene.getAssetFont(
					"assets/fonts/commodore-64.ttf"),
				sf::Vector2f(0, 0), "< ? >", sf::Color::White,
				18, "0123456789");
			inputBox->addComponent<PadderH<sfs::CustomBox>>(
				23 + i * 18, *inputBox);
			inputBox->addComponent<PadderL<sfs::CustomBox>>(
				910, *inputBox);
			_stats.emplace_back(inputBox);
		}
		_printTotal = &addChild<CharacterStatName>(
			scene,
			*scene.getAssetFont("assets/fonts/commodore-64.ttf"),
			"total :", sf::Vector2f(975, 580));
	}
	void update(sfs::Scene &) noexcept
	{
		float total = 100;
		for (auto &i : _stats) {
			if (i->string() != "") {
				total -= std::atoi(i->string().c_str());
			}
		}
		_total = total;
		_printTotal->setString("total\n "
				       + std::to_string((int)_total));
	}
	void onEvent(sfs::Scene &scene[[gnu::unused]],
		     const sf::Event &event) noexcept
	{
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Down
			    || event.key.code == sf::Keyboard::Tab)
				for (int i = 0; i < 5; i += 1) {
					if (_stats[i]->getSelected() == true) {
						_stats[i]->toggle(false);
						if (i < 4)
							_stats[i + 1]->toggle(
								true);
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

      protected:
	sfs::InputBox *_box;
	std::vector<sfs::CustomBox *> _stats;
	CharacterStatName *_printTotal;
	float _total = 100;
};

class CharacterSelector : public sfs::GameObject
{
      public:
	CharacterSelector() noexcept
	    : _navbar(nullptr), _image(nullptr), _name(nullptr),
	      _creator(nullptr){};
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;
	void addCharacter(Character &character) noexcept
	{
		_characters.push_back(character);
	};
	void loadCharactersFromFile(const std::string &path) noexcept;
	void removeCharacter(const std::string &name) noexcept
	{
		for (auto it = _characters.begin(); it != _characters.end();
		     ++it) {
			if (name == it->getName()) {
				_characters.erase(it);
				return;
			}
		}
	}

      protected:
	std::vector<Character> _characters;
	sfs::Hnavbar *_navbar;
	sfs::Sprite *_image;
	sfs::Text *_name;
	CharacterCreation *_creator;
};
} // namespace cf
