#include "MainMenu.hpp"
#include <Padder.hpp>

namespace cf {

void MainMenu::start(sfs::Scene &scene) noexcept
{
	_quotes = &addChild<QuoteGenerator>(scene, sf::Vector2f(1170, 70));
	_exit = &addChild<ExitButton>(scene);
	_play = &addChild<PlayButton>(scene);
	createOptionsButton(scene);
}

void MainMenu::createOptionsButton(sfs::Scene &scene) noexcept
{
	auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton1.png");
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
	_play->destroy();
	_play = nullptr;
	_quotes->destroy();
	_quotes = nullptr;
	_options->destroy();
	_options = nullptr;
	_exit->destroy();
	_exit = nullptr;
	_optionImage = &addChild<Background>(scene);
	_optionImage->addVelocity(sf::Vector2f(0, -650));
	_scroller->setLayersSpeed(scene, false, sf::Vector2f(0, -650));
}

static bool lock = false;

void MainMenu::update(sfs::Scene &scene) noexcept
{
	if (_optionImage != nullptr) {
		if (_optionImage->getPosition().y <= 0) {
			if (_opS == nullptr) {
				_opS = &addChild<optionScene>(scene);
			}
			if (_opS != nullptr && lock == false) {
				auto check = scene.getGameObjects<optionScene>();
				if (check.size() == 0) {
					lock = true;
					_optionImage->addVelocity(sf::Vector2f(0, 650));
					_scroller->setLayersSpeed(scene, false,
								  sf::Vector2f(0, 650));
				}
			}
		}
	}
	if (lock == true && _optionImage->getPosition().y >= 1350) {
		_optionImage->destroy();
		_optionImage = nullptr;
		_opS = nullptr;
		lock = false;
		_scroller->setLayersSpeed(scene, true);
		_quotes = &addChild<QuoteGenerator>(scene, sf::Vector2f(1170, 70));
		_play = &addChild<PlayButton>(scene);
		_exit = &addChild<ExitButton>(scene);
		createOptionsButton(scene);
	}
}
} // namespace cf
