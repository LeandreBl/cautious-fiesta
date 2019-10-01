#pragma once

#include <GameObject.hpp>
#include <WScene.hpp>
#include "PaddedSprite.hpp"
#include "Button.hpp"

namespace cf
{

  
  class QuoteGenerator : public sfs::GameObject
  {
  public:
  protected:
  };

  
  class ExitButton : public sfs::GameObject
  {
  public:
    ExitButton() noexcept {};
    void start(sfs::Scene &scene) noexcept;
    void update(sfs::Scene &scene) noexcept {};
  protected:
    void closeScene(sfs::Scene &scene) const noexcept;
  };

  
  class MainMenu : public sfs::GameObject
  {
  public:
    MainMenu() noexcept
    : _background(nullptr)
    {};
    void start(sfs::Scene &scene) noexcept;
    void update(sfs::Scene &scene) noexcept;
    void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;
  protected:
    sfs::Sprite *_background;
  };
  
  
} // namespace cf
