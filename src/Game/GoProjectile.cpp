#include <math.h>

#include <Sound.hpp>
#include "GoProjectile.hpp"

namespace cf {
GoProjectile::GoProjectile(uint64_t id, const sf::Vector2f &position, float angle, float speed,
			   const sf::Color &color, const sf::Texture &texture, const std::vector<sf::IntRect> &conteiners) noexcept
	: UdpGameObject(id)
	, _velocity(addComponent<sfs::Velocity>(
		  sf::Vector2f(cosf(angle) * speed, sinf(angle) * speed)))
	, _sprites(addComponent<sfs::MultiSprite>(texture, conteiners, 0.5))
	, _color(color)
{
	_sprites.setColor(color);
	setPosition(position);
}

void GoProjectile::start(sfs::Scene &scene) noexcept
{
	addComponent<sfs::Sound>(*scene.getAssetSoundBuffer("local-assets/musics/laser.ogg"), false, true);
}
} // namespace cf