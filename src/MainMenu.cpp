#include <iostream>
#include "MainMenu.hpp"

namespace cf
{
  void MainMenu::start(sfs::Scene &scene) noexcept
  {
    _scroller = &addChild<sfs::GameObject>(scene);
    _scroller->addChild<Layers>(scene, "assets/sprites/Nuages.jpg", sf::Vector2f(1.2, 1), sf::Vector2f(-150, 0));
    _scroller->addChild<Layers>(scene, "assets/sprites/test.png", sf::Vector2f(1, 2.5), sf::Vector2f(-200, 0), sf::Vector2f(0, 190));
    _scroller->addChild<Layers>(scene, "assets/sprites/imeubles.png", sf::Vector2f(1, 2.5), sf::Vector2f(-350, 0), sf::Vector2f(0, 800));
    _scroller->addChild<Layers>(scene, "assets/sprites/FirstLayer.png", sf::Vector2f(1, 2), sf::Vector2f(-400, 0), sf::Vector2f(0, 910));
    
    addChild<QuoteGenerator>(scene);
    addChild<ExitButton>(scene);
    addChild<OptionsButton>(scene);
    addChild<PlayButton>(scene);
    addChild<IpInputBox>(scene);
    addChild<NavBar>(scene);

    scene.subscribe(*this, sf::Event::Closed);
    
    auto *sound = scene.getAssetSoundBuffer("assets/musics/menuMusic.ogg");
    addComponent<sfs::Sound>(*sound, true, true);
  }
  
  void MainMenu::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
  {
    if (event.type == sf::Event::Closed)
      scene.close();
  }
}
