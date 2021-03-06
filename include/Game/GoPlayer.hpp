#include <BasicShape.hpp>

#include "Velocity.hpp"
#include "Sound.hpp"
#include "UdpGameObject.hpp"
#include "Udp.hpp"

namespace cf {
class GameManager;
class GoPlayer : public UdpGameObject {
      public:
	struct stats {
		float life;
		float speed;
		float attack;
		float attackSpeed;
		float armor;
	};
	GoPlayer(GameManager &manager, uint64_t id, const std::string &name,
		 const struct stats &stats, const sf::Color &color, const std::string &sprite,
		 UdpPrctl::weaponType weaponType) noexcept;
	void onDestroy() noexcept;
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;
	void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;

	sfs::Sound &getAttackSound() noexcept;

      protected:
	GameManager &_manager;
	struct stats _stats;
	sf::Color _color;
	std::string _spriteName;
	sfs::Sprite *_playerSprite;
	sfs::Text *_playerName;
	sfs::Velocity &_velocity;
	sfs::Sound *_sound;
	sf::Vector2f _lastMousePos;
};
} // namespace cf