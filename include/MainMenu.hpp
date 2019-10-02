#pragma once

#include <iostream>
#include <GameObject.hpp>
#include <WScene.hpp>
#include "PaddedSprite.hpp"
#include "Button.hpp"
#include "Hnavbar.hpp"
#include "InputBox.hpp"
#include "MainMenuButtons.hpp"
#include "Music.hpp"

namespace cf
{

  
  class QuoteGenerator : public sfs::GameObject
  {
  public:
    QuoteGenerator() noexcept
    : _text(nullptr), _font(nullptr), _scale(1), _rev(1)
    {};
    void start(sfs::Scene &scene) noexcept;
    void update(sfs::Scene &scene) noexcept;
  protected:
    sfs::Text *_text;
    const sf::Font *_font;
    float _scale;
    int _rev;
  };


  class NavBar : public sfs::UI
  {
  public:
    void start(sfs::Scene &scene) noexcept;
    void update(sfs::Scene &scene) noexcept {};
  protected:
  };


  class IpInputBox : public sfs::GameObject
  {
  public:
    void start(sfs::Scene &scene) noexcept;
  protected:
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
