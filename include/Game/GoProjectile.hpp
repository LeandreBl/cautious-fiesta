#pragma once

#include "BasicShape.hpp"
#include "GameObject.hpp"
#include "Velocity.hpp"
#include "UdpGameObject.hpp"

namespace cf {
class GoProjectile : public UdpGameObject {
      public:
	GoProjectile(uint64_t id, const sf::Vector2f &position, float angle, float speed,
		     const sf::Color &color, const sf::Texture &texture,
		     const std::vector<sf::IntRect> &conteiners) noexcept;

      protected:
	sfs::Velocity &_velocity;
	sfs::MultiSprite &_sprites;
	sf::Color _color;
};
} // namespace cf