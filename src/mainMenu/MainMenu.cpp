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
		std::bind(&MainMenu::launchOptionScene, this, std::ref(scene)), "Options",
		sf::Color::White, 25);
	_options->setScale(sf::Vector2f(1.2, 1.7));
	_options->addComponent<PadderR<sfs::Button>>(25.f, *_options);
	_options->addComponent<PadderB<sfs::Button>>(25.f, *_options);
}

void MainMenu::launchOptionScene(sfs::Scene &scene) noexcept
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
	_optionImage = &addChild<optionBackground>(scene); // TODO modifier ça
	for (auto &i : _layers) {
		auto velo = i->getComponents<sfs::Velocity>();
		velo[0]->destroy();
		i->setVelocity(sf::Vector2f(0, -650));
	}
}

void MainMenu::start(sfs::Scene &scene) noexcept
{
	_scroller = &addChild<Scroller>(scene);
	_quotes = &addChild<QuoteGenerator>(scene);
	_exit = &addChild<ExitButton>(scene);
	_play = &addChild<PlayButton>(scene);
	createOptionsButton(scene);

	scene.subscribe(*this, sf::Event::Closed);

	auto *sound = scene.getAssetSoundBuffer("assets/musics/menuMusic.ogg");
	addComponent<sfs::Sound>(*sound, true, true);
}

void MainMenu::update(sfs::Scene &scene) noexcept
{
	if (_optionImage != nullptr) {
		if (_optionImage->getPosition().y <= 0) {
			if (_opS == nullptr) {
				_opS = &addChild<optionScene>(scene);			
			}
		}
	}
}

void MainMenu::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::Closed)
		scene.close();
}
} // namespace cf
