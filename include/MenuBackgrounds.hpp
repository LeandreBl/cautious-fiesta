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
    DrawLayers(const sf::Texture &texture, const sf::Vector2f &origin = sf::Vector2f(0, 0)) noexcept
      : Sprite(texture), _origin(origin)
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
	pos.x = _origin.x;
	ob.setPosition(pos);
      }
      sfs::Sprite::update(scene, ob);
    }
  protected:
    sf::Vector2f _origin;
  };
  
  class Layers : public sfs::GameObject
  {
  public:
    Layers(const std::string &path, const sf::Vector2f &scale = sf::Vector2f(1, 1),
	   const sf::Vector2f &speed = sf::Vector2f(0, 0), const sf::Vector2f &origin = sf::Vector2f(0, 0)) noexcept
      : _texture(nullptr), _path(path), _scale(scale), _speed(speed), _origin(origin)
    {setPosition(_origin);};
    void start(sfs::Scene &scene) noexcept;
  protected:
    const sf::Texture *_texture;
    const std::string _path;
    const sf::Vector2f _scale;
    const sf::Vector2f _speed;
    const sf::Vector2f _origin;
  };
}
