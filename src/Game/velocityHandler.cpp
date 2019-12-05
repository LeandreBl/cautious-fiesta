#include "GameManager.hpp"
#include "UdpConnection.hpp"
#include "GoPlayer.hpp"

namespace cf {
int UdpConnect::velocityHandler(sfs::Scene &scene, GameManager &manager, Serializer &s)
{
	uint64_t id;
	sf::Vector2f acceleration;
	sf::Vector2f speed;

	s >> id >> speed >> acceleration;
	id += 1000;
	auto *go = scene.getGameObject(id);
	if (go == nullptr) {
		std::cerr << "Can't find object " << id << std::endl;
		return -1;
	}
	auto v = go->getComponents<sfs::Velocity>();
	for (auto &&i : v) {
		i->acceleration = acceleration;
		i->speed = speed;
	}
	return 0;
}
} // namespace cf