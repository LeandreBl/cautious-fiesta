#pragma once

#include "BasicShape.hpp"
#include "GameObject.hpp"
#include "Velocity.hpp"

namespace cf {
class GoProjectile : public sfs::GameObject {
      public:
	GoProjectile(const sf::Vector2f &position, const sf::Vector2f &speed,
		     const sf::Vector2f &acceleration, const sf::Color &color,
		     const sf::Texture &texture) noexcept;

      protected:
	sfs::Velocity &_velocity;
	sfs::Sprite &_sprite;
	sf::Color _color;
};
} // namespace cf