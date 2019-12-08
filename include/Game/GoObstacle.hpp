#pragma once

#include "BasicShape.hpp"
#include "GameObject.hpp"
#include "UdpGameObject.hpp"

namespace cf {
class GoObstacle : public UdpGameObject {
      public:
	GoObstacle(uint64_t id, const sf::Vector2f &position, const sf::Texture &texture, 
    const std::vector<sf::IntRect> &conteiners) noexcept;
	void start(sfs::Scene &scene) noexcept;
      protected:
	sfs::MultiSprite &_sprites;
};
} // namespace cf