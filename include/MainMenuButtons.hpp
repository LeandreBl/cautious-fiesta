#pragma once

#include <iostream>
#include <GameObject.hpp>
#include <WScene.hpp>
#include "Button.hpp"

namespace cf
{
  class ExitButton : public sfs::GameObject
  {
  public:
    ExitButton() noexcept {};
    void start(sfs::Scene &scene) noexcept;
  protected:
    void closeScene(sfs::Scene &scene) const noexcept;
  };


  class OptionsButton : public sfs::GameObject
  {
  public:
    void start(sfs::Scene &scene) noexcept;
  protected:
    void optionScene() noexcept;
  };

  class PlayButton : public sfs::GameObject
  {
  public:
    void start(sfs::Scene &scene) noexcept;
  protected:
    void play() noexcept;
  };
}
