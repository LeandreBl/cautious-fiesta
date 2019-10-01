#include <iostream>
#include "MainMenu.hpp"

namespace cf
{
  
  void ExitButton::closeScene(sfs::Scene &scene) const noexcept
  {
    scene.close();
  }

  void ExitButton::start(sfs::Scene &scene) noexcept
  {
    auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
    auto texture = scene.getAssetTexture("assets/sprites/blank.png");
    
    if (font == nullptr || texture == nullptr) {
      errorLog("[Menu] could not load the font or the texture");
      scene.close();
    }

    auto &button = addChild<sfs::Button>(scene,
					 sf::Vector2f(0, 0),
					 *texture,
					 std::bind(&ExitButton::closeScene, this, std::ref(scene)),
					 *font,
					 "Quit",
					 sf::Color::White,
					 22);
    
    button.addComponent<PadderL<sfs::Button>>(25.f, button);
    button.addComponent<PadderB<sfs::Button>>(25.f, button);
    
    button.setScale(sf::Vector2f(1, 1.5));
  }
  
  void MainMenu::start(sfs::Scene &scene) noexcept
  {

    //auto backTexture = scene.getAssetTexture("/home/jb/Projets/cautious-fiesta/assets/menu.png");
    //_background = &addComponent<sfs::Sprite>(*backTexture);
    //_background->setScale(2, 4);
    
    addChild<QuoteGenerator>(scene);
    addChild<ExitButton>(scene);
    scene.subscribe(*this, sf::Event::Closed);
  }

  void MainMenu::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
  {
    if (event.type == sf::Event::Closed)
      scene.close();
  }
  
  void MainMenu::update(sfs::Scene &scene) noexcept
  {
   
  }
} // namespace cf
