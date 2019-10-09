#include <fstream>
#include "CharacterSelector.hpp"

namespace cf
{

static const char *_statsNames[] = {"life", "speed", "attack", "att speed",
				    "armor"};

void CharacterSelector::start(sfs::Scene &scene) noexcept
{
	_navbar = &addChild<sfs::Hnavbar>(scene, sf::Vector2f(0, 0),
					  sf::Vector2f(16, 150),
					  sf::Color::White);
	_navbar->addComponent<PadderW<sfs::Hnavbar>>(-285, *_navbar);
	_navbar->addComponent<PadderH<sfs::Hnavbar>>(46, *_navbar);
	_image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/CharacterSelection.png"),
										sf::Vector2f(690, 510));
	_image->setScale(sf::Vector2f(1.2, 1.5));
	addComponent<sfs::Text>(
		*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "NAME",
		sf::Color::White, 20, sf::Vector2f(1110, 528));
	addComponent<sfs::Text>(
		*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "STATS",
		sf::Color::White, 20, sf::Vector2f(885, 528));
	for (int i = 0; i < 5; ++i) {
		addChild<Text>(
			scene,
			*scene.getAssetFont("assets/fonts/commodore-64.ttf"),
			_statsNames[i], sf::Vector2f(770, 557 + 18 * i));
		_stats.emplace_back(&addChild<Text>(scene, *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
		                                                 "", sf::Vector2f(910, 557 + 18 * i)));
	}
	_name = &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"),"",
									sf::Color::White, 20, sf::Vector2f(1082, 590));
	loadCharactersFromFile();
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
			for (int i = 0; i < 5; i += 1)
				_stats[i]->setString(std::to_string((int)data[i]));
		} else if (_navbar->getValue() == 1) {
			if (_creator == nullptr) {
				_creator = &addChild<CharacterCreation>(scene);
				auto button = &_creator->addChild<sfs::Button>(scene,
					*scene.getAssetTexture("assets/sprites/blank.png"),
					*scene.getAssetFont("assets/fonts/commodore-64.ttf"),
					sf::Vector2f(-1000, 0),
					std::bind(&CharacterSelector::addCharacterFromCreateButton, this),
					"create", sf::Color::White, 15);
				button->addComponent<PadderH<sfs::Button>>(150, *button);
				button->addComponent<PadderW<sfs::Button>>(0, *button);
			}
			_name->setString("");
			for (auto &i : _stats)
				i->setString("");
		}
	} else {
		if (_creator == nullptr) {
			_creator = &addChild<CharacterCreation>(scene);
			auto button = &_creator->addChild<sfs::Button>(
				scene,
				*scene.getAssetTexture(
					"assets/sprites/blank.png"),
				*scene.getAssetFont(
					"assets/fonts/commodore-64.ttf"),
				sf::Vector2f(0, 0),
				std::bind(&CharacterSelector::
						  addCharacterFromCreateButton,
					  this),
				"create", sf::Color::White, 15);
			button->addComponent<PadderH<sfs::Button>>(150,
								   *button);
			button->addComponent<PadderW<sfs::Button>>(0, *button);
		}
	}
}

void CharacterSelector::writeCharacterInFile() noexcept
{
	std::ofstream myfile;

	myfile.open(_path, std::ios::binary | std::ios::app);
	if (!myfile.is_open())
		return;
	Serializer s;
	s.set(_characters.back().getName());
	s.set(_characters.back().getStats());
	myfile.write(static_cast<const char *>(s.getNativeHandle()),
		     s.getSize());
	myfile.close();
}

void CharacterSelector::loadCharactersFromFile() noexcept
{
	std::ifstream stream;

	stream.open(_path, std::ios::binary);
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
		s.get(name);
		s.get(stats);
		_characters.emplace_back(name, stats);
	}
	stream.close();
}
} // namespace cf
