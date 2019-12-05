#include <BasicShape.hpp>

#include "Velocity.hpp"
#include "UdpGameObject.hpp"
#include "Udp.hpp"

namespace cf {
class GoWeapon : public UdpGameObject {
      public:
	GoWeapon(uint64_t id, uint64_t playerId, const sf::Texture &texture) noexcept;
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;

      protected:
	uint64_t _playerId;
	sfs::Sprite &_weaponSprite;
};
} // namespace cf