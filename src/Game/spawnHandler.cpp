#include "GameManager.hpp"
#include "UdpConnection.hpp"
#include "GoPlayer.hpp"

namespace cf {

static void spawnPlayer(sfs::Scene &scene, Serializer &s, uint64_t id)
{
	sf::Color color;
	struct GoPlayer::stats stats;
	std::string name;
	std::string sprite;
	int32_t weaponType;

	s >> name;
	s >> stats.life;
	s >> stats.speed;
	s >> stats.attack;
	s >> stats.attackSpeed;
	s >> stats.armor;
	s >> color;
	s >> sprite;
	s >> weaponType;
	std::cout << name << " " << stats.life << " " << stats.speed << " " << stats.attack << " "
		  << stats.attackSpeed << " " << stats.armor << " (" << (int)color.r << ", "
		  << (int)color.g << ", " << (int)color.b << ") " << sprite << " " << weaponType
		  << std::endl;
	scene.addGameObject<GoPlayer>(id, name, stats, color, sprite,
				      static_cast<UdpPrctl::weaponType>(weaponType));
}

int UdpConnect::spawnHandler(sfs::Scene &scene, GameManager &manager, Serializer &s)
{
	int32_t type;
	uint64_t id;

	s >> type;
	s >> id;
	std::cout << "spawn " << type << " " << id << std::endl;
	switch (static_cast<UdpPrctl::spawnType>(type)) {
	case UdpPrctl::spawnType::PLAYER:
		spawnPlayer(scene, s, id);
		break;
	case UdpPrctl::spawnType::OBSTACLE:
		break;
	};
	return 0;
}
} // namespace cf