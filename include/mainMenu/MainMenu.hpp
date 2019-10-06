#pragma once

#include <iostream>
#include <GameObject.hpp>
#include <WScene.hpp>
#include <Sound.hpp>
#include "PaddedSprite.hpp"
#include "Button.hpp"
#include "Hnavbar.hpp"
#include "InputBox.hpp"
#include "MenuButtons.hpp"
#include "MenuBackgrounds.hpp"
#include "MenuUi.hpp"

namespace cf
{
  class MainMenu : public sfs::GameObject
  {
  public:
    MainMenu() noexcept
    : _scroller(nullptr)
    {};
    void start(sfs::Scene &scene) noexcept;
    void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;
  protected:
    sfs::GameObject *_scroller;
  };  
}
