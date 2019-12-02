#include <BasicShape.hpp>

#include "Velocity.hpp"
#include "UdpGameObject.hpp"
#include "Udp.hpp"

namespace cf
{
class GoPlayer : public UdpGameObject
{
public:
	struct stats
	{
		float life;
		float speed;
		float attack;
		float attackSpeed;
		float armor;
	};
	GoPlayer(uint64_t id, const std::string &name, const struct stats &stats,
			 const sf::Color &color, const std::string &sprite,
			 UdpPrctl::weaponType weaponType) noexcept;
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;

protected:
	struct stats _stats;
	sf::Color _color;
	std::string _spriteName;
	sfs::Sprite *_playerSprite;
	sfs::Text *_playerName;
	sfs::Velocity &_velocity;
	// weapon todo
};
} // namespace cf