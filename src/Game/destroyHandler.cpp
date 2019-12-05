#include "UdpConnection.hpp"

namespace cf {
int UdpConnect::destroyHandler(sfs::Scene &scene, GameManager &manager, Serializer &s)
{
	uint64_t id;
	int32_t type;

	s >> type;
	s >> id;
	id += 1000;
	auto *go = scene.getGameObject(id);
	if (go == nullptr) {
		std::cerr << "go: " << id << " not found" << std::endl;
		return -1;
	}
	if (static_cast<UdpPrctl::destroyType>(type) == UdpPrctl::destroyType::COMPONENT) {
		uint64_t cid;
		s >> cid;
		for (auto &&i : go->getComponents()) {
			if (i->getId() == cid) {
				i->destroy();
				return 0;
			}
		}
	}
	else if (static_cast<UdpPrctl::destroyType>(type) == UdpPrctl::destroyType::GAMEOBJECT) {
		go->destroy();
	}
	return 0;
}
} // namespace cf