#include "GameManager.hpp"
#include "UdpConnection.hpp"
#include "GoPlayer.hpp"

namespace cf {
int UdpConnect::positionHandler(sfs::Scene &scene, GameManager &manager, Serializer &s)
{
	uint64_t id;
	sf::Vector2f position;

	s >> id;
	s >> position;
	auto *go = scene.getGameObject(id);
	if (go == nullptr) {
		std::cerr << "Can't find object " << id << std::endl;
		return -1;
	}
	go->setPosition(position);
	return 0;
}
} // namespace cf