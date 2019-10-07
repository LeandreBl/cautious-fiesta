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
#include "Option.hpp"

namespace cf
{
  class MainMenu : public sfs::GameObject
  {
  public:
    MainMenu() noexcept
    : _scroller(nullptr), _play(nullptr), _quotes(nullptr), _exit(nullptr), _options(nullptr)
    {};
    void start(sfs::Scene &scene) noexcept;
    void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;
    void createOptionsButton(sfs::Scene &scene) noexcept;
    void OptionScene(sfs::Scene &scene) noexcept;
  protected:
    Layers *_scroller;
    PlayButton *_play;
    QuoteGenerator *_quotes;
    ExitButton *_exit;
    sfs::Button *_options;
  };  
}
