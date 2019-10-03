#include <iostream>
#include "MainMenu.hpp"

namespace cf
{
  void MainMenu::start(sfs::Scene &scene) noexcept
  {
    _scroller = &addChild<sfs::GameObject>(scene);
    _scroller->addChild<Layers>(scene, "assets/sprites/Nuages.jpg");
    
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
