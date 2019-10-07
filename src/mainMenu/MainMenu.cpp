#include <iostream>
#include "MainMenu.hpp"

namespace cf
{

void MainMenu::createOptionsButton(sfs::Scene &scene) noexcept {
	auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture("assets/sprites/blank.png");
	if (font == nullptr || texture == nullptr) {
		errorLog("[Menu] could not load the font or the texture");
		destroy();
		return;
	}
	_options = &addChild<sfs::Button>(
		scene, *texture, *font, sf::Vector2f(0, 0),
		std::bind(&MainMenu::OptionScene, this, std::ref(scene)), "Options",
		sf::Color::White, 25);
	_options->setScale(sf::Vector2f(1.2, 1.7));
	_options->addComponent<PadderR<sfs::Button>>(25.f, *_options);
	_options->addComponent<PadderB<sfs::Button>>(25.f, *_options);
}

void MainMenu::OptionScene(sfs::Scene &scene) noexcept
{
	std::cout << "options activées" << std::endl;
	if (_play != nullptr && _quotes != nullptr && _options != nullptr) {
		_play->destroy();
		_play = nullptr;
		_quotes->destroy();
		_quotes = nullptr;
		_options->destroy();
		_options = nullptr;
	}
	auto _layers = scene.getGameObjects<Layers>();
	addChild<optionBackground>(scene); // TODO modifier ça
	for (auto &i : _layers) {
		auto velo = i->getComponents<sfs::Velocity>();
		velo[0]->destroy();
		i->setVelocity(sf::Vector2f(0, -550));
	}
}

void MainMenu::start(sfs::Scene &scene) noexcept
{
	_scroller = &addChild<Layers>(scene, "assets/sprites/Nuages.jpg",
				    sf::Vector2f(1.2, 1.2),
				    sf::Vector2f(-150, 0));
	_scroller->addChild<Layers>(scene, "assets/sprites/trainBackground.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-300, 0),
				    sf::Vector2f(0, 930));
	_scroller->addChild<Layers>(scene, "assets/sprites/test.png",
				    sf::Vector2f(1, 2.5), sf::Vector2f(-250, 0),
				    sf::Vector2f(0, 190));
	_scroller->addChild<Layers>(scene, "assets/sprites/rangéImeubles.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-325, 0),
				    sf::Vector2f(0, 600));
	_scroller->addChild<Layers>(scene, "assets/sprites/Mimeubles.png",
				    sf::Vector2f(1, 2.5), sf::Vector2f(-350, 0),
				    sf::Vector2f(0, 515));
	//_scroller->addChild<Layers>(scene, "assets/sprites/imeubles.png",
	//sf::Vector2f(1, 2.5), sf::Vector2f(-350, 0), sf::Vector2f(0, 800));
	_scroller->addChild<Layers>(scene, "assets/sprites/traks.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-500, 0),
				    sf::Vector2f(0, 1040));
	_scroller->addChild<Layers>(scene, "assets/sprites/train.png",
				    sf::Vector2f(0.5, 0.5),
				    sf::Vector2f(550, 0), sf::Vector2f(0, 979));
	_scroller->addChild<Layers>(scene, "assets/sprites/FirstLayer.png",
				    sf::Vector2f(1, 2), sf::Vector2f(-550, 0),
				    sf::Vector2f(0, 930));

	_quotes = &addChild<QuoteGenerator>(scene);
	_exit = &addChild<ExitButton>(scene);
	_play = &addChild<PlayButton>(scene);
	createOptionsButton(scene);

	scene.subscribe(*this, sf::Event::Closed);

	auto *sound = scene.getAssetSoundBuffer("assets/musics/menuMusic.ogg");
	addComponent<sfs::Sound>(*sound, true, true);
}

void MainMenu::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::Closed)
		scene.close();
}
} // namespace cf
