#include <math.h>

#include "GoProjectile.hpp"

namespace cf {
GoProjectile::GoProjectile(uint64_t id, const sf::Vector2f &position, float angle, float speed,
			   const sf::Color &color, const sf::Texture &texture) noexcept
	: UdpGameObject(id)
	, _velocity(addComponent<sfs::Velocity>(
		  sf::Vector2f(cosf(angle) * speed, sinf(angle) * speed)))
	, _sprite(addComponent<sfs::Sprite>(texture))
	, _color(color)
{
	setPosition(position);
}
} // namespace cf