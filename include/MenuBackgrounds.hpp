#pragma once

#include <iostream>
#include <GameObject.hpp>
#include <IComponent.hpp>
#include <SFML/Graphics.hpp>
#include <Velocity.hpp>

namespace cf
{
  class DrawLayers : public sfs::Sprite
  {
  public:
    DrawLayers(const sf::Texture &texture) noexcept
      : Sprite(texture)
    {};
    void display(sf::RenderWindow &window) noexcept
    {
      auto pos = getPosition();
      window.draw(*this);
      pos.x += getGlobalBounds().width;
      setPosition(pos);
      window.draw(*this);
    }
    void update(sfs::Scene &scene, sfs::GameObject &ob) noexcept
    {
      auto pos = ob.getPosition();
      if (pos.x <=  (0 - getGlobalBounds().width)) {
	pos.x = 0;
	ob.setPosition(pos);
      }
      sfs::Sprite::update(scene, ob);
    }
  protected:
  };
  
  class Layers : public sfs::GameObject
  {
  public:
    Layers(const std::string &path) noexcept
      : _texture(nullptr), _path(path)
    {};
    void start(sfs::Scene &scene) noexcept;
  protected:
    const sf::Texture *_texture;
    const std::string _path;
  };
}
