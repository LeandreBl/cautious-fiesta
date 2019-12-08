#include "GoObstacle.hpp"

namespace cf {
GoObstacle::GoObstacle(uint64_t id, const sf::Vector2f &position, 
const sf::Texture &texture, const std::vector<sf::IntRect> &conteiners) noexcept
	: UdpGameObject(id)
	, _sprites(addComponent<sfs::MultiSprite>(texture, conteiners, 0.5))
{
	setPosition(position);
}

void GoObstacle::start(sfs::Scene &scene) noexcept
{
}
} // namespace cf