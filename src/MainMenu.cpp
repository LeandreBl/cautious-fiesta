#include <iostream>
#include "MainMenu.hpp"

namespace cf
{
void MainMenu::start(sfs::Scene &scene) noexcept
{
	_scroller = &addChild<sfs::GameObject>(scene);
	_scroller->addChild<Layers>(scene, "assets/sprites/Nuages.jpg",
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

	addChild<QuoteGenerator>(scene);
	addChild<ExitButton>(scene);
	addChild<OptionsButton>(scene);
	addChild<PlayButton>(scene);

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
