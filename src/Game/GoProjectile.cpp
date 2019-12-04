#include "GoProjectile.hpp"

namespace cf {
GoProjectile::GoProjectile(const sf::Vector2f &position, const sf::Vector2f &speed,
			   const sf::Vector2f &acceleration, const sf::Color &color,
			   const sf::Texture &texture) noexcept
	: _velocity(addComponent<sfs::Velocity>(speed, acceleration))
	, _sprite(addComponent<sfs::Sprite>(texture))
	, _color(color)
{
	setPosition(position);
}
} // namespace cf