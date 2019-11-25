#include <fstream>
#include <iomanip>

#include <Button.hpp>
#include <Vnavbar.hpp>
#include <Padder.hpp>

#include "CharacterSelector.hpp"

namespace cf {

static const char *_statsNames[] = {"life", "speed", "attack", "att speed", "armor"};

void CharacterSelector::start(sfs::Scene &scene) noexcept
{
	_navbar = &addChild<sfs::Vnavbar>(scene, sf::Vector2f(0, 0), sf::Vector2f(16, 150),
					  sf::Color::White);
	_navbar->addComponent<PadderW<sfs::Vnavbar>>(-285, *_navbar);
	_navbar->addComponent<PadderH<sfs::Vnavbar>>(46, *_navbar);
	_image = &addComponent<sfs::Sprite>(
		*scene.getAssetTexture("local-assets/sprites/Menu/ui/CharacterSelection.png"),
		sf::Vector2f(690, 510));
	_image->setScale(sf::Vector2f(1.2, 1.5));
	addComponent<sfs::Text>(*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), "NAME",
				sf::Color::White, 20, sf::Vector2f(1110, 528));
	addComponent<sfs::Text>(*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), "STATS",
				sf::Color::White, 20, sf::Vector2f(885, 528));
	for (int i = 0; i < 5; ++i) {
		addChild<Text>(scene, *scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
			       _statsNames[i], sf::Vector2f(770, 557 + 18 * i));
		_stats.emplace_back(&addChild<Text>(
			scene, *scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), "",
			sf::Vector2f(910, 557 + 18 * i)));
	}
	_name = &addComponent<sfs::Text>(*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
					 "", sf::Color::White, 20, sf::Vector2f(1082, 590));
	loadCharactersFromFile();
	_hat = &addComponent<sfs::Sprite>(
		*scene.getAssetTexture("local-assets/sprites/Menu/hat.png"),
		sf::Vector2f(699, 575));
}

void CharacterSelector::update(sfs::Scene &scene) noexcept
{
	if (_characters.size() != 0) {
		float characterSelected = _characters.size() * _navbar->getValue();
		if (_navbar->getValue() < 1) {
			if (_creator != nullptr) {
				_creator->destroy();
				_creator = nullptr;
			}
			_name->setString(_characters.at((int)characterSelected).getName());
			float data[5];
			data[0] = _characters.at((int)characterSelected).getLife();
			data[1] = _characters.at((int)characterSelected).getSpeed();
			data[2] = _characters.at((int)characterSelected).getAttack();
			data[3] = _characters.at((int)characterSelected).getAttackSpeed();
			data[4] = _characters.at((int)characterSelected).getArmor();
			_hat->setColor(_characters.at((int)characterSelected).getColor());
			std::ostringstream stream;
			stream << std::fixed << std::setprecision(1);
			for (int i = 0; i < 5; i += 1) {
				stream.str("");
				stream.clear();
				stream << data[i];
				_stats[i]->setString(stream.str());
			}
		}
		else if (_navbar->getValue() == 1) {
			if (_creator == nullptr) {
				_creator = &addChild<CharacterCreation>(scene);
				auto button = &_creator->addChild<sfs::Button>(
					scene,
					*scene.getAssetTexture(
						"local-assets/sprites/Menu/ui/BlankButton1.png"),
					*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
					sf::Vector2f(-1000, 0),
					std::bind(&CharacterSelector::addCharacterFromCreateButton,
						  this),
					"create", sf::Color::White, 15);
				button->addComponent<PadderH<sfs::Button>>(150, *button);
				button->addComponent<PadderW<sfs::Button>>(0, *button);
			}
			_name->setString("");
			for (auto &i : _stats)
				i->setString("");
		}
	}
	else {
		if (_creator == nullptr) {
			_creator = &addChild<CharacterCreation>(scene);
			auto button = &_creator->addChild<sfs::Button>(
				scene,
				*scene.getAssetTexture(
					"local-assets/sprites/Menu/ui/BlankButton1.png"),
				*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
				sf::Vector2f(0, 0),
				std::bind(&CharacterSelector::addCharacterFromCreateButton, this),
				"create", sf::Color::White, 15);
			button->addComponent<PadderH<sfs::Button>>(150, *button);
			button->addComponent<PadderW<sfs::Button>>(0, *button);
		}
	}
}

void CharacterSelector::writeCharacterInFile() noexcept
{
	std::ofstream myfile;

	if (!std::filesystem::exists(_directory))
		std::filesystem::create_directories(_directory);
	myfile.open(_directory / _filename, std::ios::binary | std::ios::app);
	if (!myfile.is_open())
		return;
	Serializer s;
	s << _characters.back().getName();
	s << _characters.back().getStats();
	s << _characters.back().getColor();
	myfile.write(static_cast<const char *>(s.getNativeHandle()), s.getSize());
	myfile.close();
}

void CharacterSelector::loadCharactersFromFile() noexcept
{
	std::ifstream stream;

	stream.open(_directory / _filename, std::ios::binary);
	if (!stream.is_open())
		return;
	char buffer[4096];
	Serializer s;
	std::streamsize size;
	do {
		size = stream.readsome(buffer, sizeof(buffer));
		if (size < 0)
			return;
		s.nativeSet(buffer, size);
	} while (size == sizeof(buffer));
	while (s.getSize() > 0) {
		std::string name;
		struct Character::stats stats;
		sf::Color color;
		s >> name;
		s >> stats;
		s >> color;
		_characters.emplace_back(name, stats, color);
	}
	stream.close();
}
} // namespace cf
