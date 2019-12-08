#pragma once

#include "BasicShape.hpp"
#include "GameObject.hpp"
#include "Velocity.hpp"
#include "UdpGameObject.hpp"

namespace cf {
class GoProjectile : public UdpGameObject {
      public:
	GoProjectile(uint64_t id, const sf::Vector2f &position, float angle, float speed,
		     const sf::Color &color, const sf::Texture &texture) noexcept;
	void start(sfs::Scene &scene) noexcept;
      protected:
	sfs::Velocity &_velocity;
	sfs::Sprite &_sprite;
	sf::Color _color;
};
} // namespace cf