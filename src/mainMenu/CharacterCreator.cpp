#include <Vnavbar.hpp>
#include <Offset.hpp>
#include <Padder.hpp>
#include <iomanip>
#include "CharacterCreator.hpp"
#include "Serializer.hpp"
#include "Character.hpp"

namespace cf {

void CharacterCreation::start(sfs::Scene &scene) noexcept
{
	scene.subscribe(*this, sf::Event::KeyPressed);
	_boxName = &addChild<sfs::InputBox>(
		scene, *scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
		sf::Vector2f(-1000, 0), "< new >", sf::Color::White, 20);
	_boxName->addComponent<PadderH<sfs::InputBox>>(56, *_boxName);
	_boxName->addComponent<PadderW<sfs::InputBox>>(180, *_boxName);
	for (int i = 0; i < 5; ++i) {
		auto inputBox = &addChild<sfs::CustomBox>(
			scene, *scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
			sf::Vector2f(-1000, 0), "< ? >", sf::Color::White, 18, "0123456789.");
		inputBox->addComponent<PadderH<sfs::CustomBox>>(23 + i * 18, *inputBox);
		inputBox->addComponent<PadderL<sfs::CustomBox>>(910, *inputBox);
		_stats.emplace_back(inputBox);
	}
	_printTotal =
		&addChild<Text>(scene, *scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
				"total", sf::Vector2f(990, 555));

	_gameMananger = scene.getGameObjects<GameManager>()[0];

	_hat = &addComponent<sfs::Sprite>(
		*scene.getAssetTexture("local-assets/sprites/Menu/hat.png"),
		sf::Vector2f(699, 575));
	for (int i = 0; i < 3; i++) {
		auto colorbar =
			&addChild<sfs::Hnavbar>(scene, sf::Vector2f(0, 0), sf::Vector2f(68, 10));
		colorbar->addComponent<sfs::Offset>(this->getPosition(),
						    sf::Vector2f(697, 530 + i * 13));
		_hatColors.emplace_back(colorbar);
	}
}

void CharacterCreation::update(sfs::Scene &) noexcept
{
	float total = 100;
	std::ostringstream stream;
	for (size_t i = 0; i != _stats.size(); i += 1) {
		float value = std::atof(_stats[i]->string().c_str());
		if (i == 3)
			value *= 20;
		total -= value;
	}
	_total = total;
	stream << std::fixed << std::setprecision(1) << _total;
	_printTotal->setString("total\n " + stream.str());

	for (size_t i = 0; i != _colors.size(); i += 1)
		_colors[i] = (255 - (_hatColors[i]->getValue() * 255));
	_hat->setColor(sf::Color(_colors[0], _colors[1], _colors[2]));
}

void CharacterCreation::onEvent(sfs::Scene &, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Tab)
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
						_stats[i - 1]->toggle(true);
					else
						_stats[4]->toggle(true);
					break;
				}
			}
	}
}
Character CharacterCreation::createCharacter() noexcept
{
	float s[5];
	for (size_t i = 0; i < _stats.size(); ++i)
		s[i] = std::atof(_stats[i]->string().c_str());
	struct Character::stats stat;
	stat.life = s[0];
	stat.speed = s[1];
	stat.attack = s[2];
	stat.attackSpeed = s[3];
	stat.armor = s[4];
	std::string name = _boxName->string();
	if (name != "" && _total == 0) {
		Character newCharacter(name, stat, sf::Color(_colors[0], _colors[1], _colors[2]));
		return newCharacter;
	}
	else if (_total != 0)
		_gameMananger->_popup->push("invalid point distribution");
	else
		_gameMananger->_popup->push("Character name invalid");
	Character newCharacter("noName", stat, sf::Color());
	return newCharacter;
};
} // namespace cf