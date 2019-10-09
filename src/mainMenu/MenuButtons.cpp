#include <iostream>
#include "MainMenu.hpp"

namespace cf
{
void ExitButton::start(sfs::Scene &scene) noexcept
{
	auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture("assets/sprites/blank.png");
	if (font == nullptr || texture == nullptr) {
		errorLog(
			"[Menu] Quit button couldn't load the font or the texture");
		destroy();
		return;
	}
	auto &button = addChild<sfs::Button>(
		scene, *texture, *font, sf::Vector2f(0, 0),
		std::bind(&ExitButton::closeScene, this, std::ref(scene)),
		"Quit", sf::Color::White, 25);
	button.setScale(sf::Vector2f(1.2, 1.7));
	button.addComponent<PadderL<sfs::Button>>(25.f, button);
	button.addComponent<PadderB<sfs::Button>>(25.f, button);
}

void PlayButton::play(sfs::Scene &scene) noexcept
{
	auto gameManager = scene.getGameObjects<GameManager>();
	gameManager[0]->_character = _CSelection->charaterSelected();
	gameManager[0]->_ip = _box->getIp();
}

void PlayButton::start(sfs::Scene &scene) noexcept
{
	auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture("assets/sprites/blank.png");
	if (font == nullptr || texture == nullptr) {
		errorLog("[Menu] could not load the font or the texture");
		scene.close();
	}
	auto &button = addChild<sfs::Button>(scene, *texture, *font,
					     sf::Vector2f(0, 0),
					     std::bind(&PlayButton::play, this, std::ref(scene)),
					     "Play", sf::Color::White, 35);
	button.setScale(sf::Vector2f(1.5, 2.2));
	button.addComponent<PadderW<sfs::Button>>(0, button);
	button.addComponent<PadderH<sfs::Button>>(-200, button);

	_box = &addChild<IpInputBox>(scene);
	_CSelection = &addChild<CharacterSelector>(scene, "config/.characters.dat");
}
} // namespace cf
