#include "GameManager.hpp"
#include "UdpConnection.hpp"
#include "GoPlayer.hpp"
#include "GoWeapon.hpp"
#include "GoProjectile.hpp"

namespace cf {

static void spawnProjectile(sfs::Scene &scene, Serializer &s, uint64_t id)
{
	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Vector2f acceleration;
	sf::Color color;
	std::string spriteName;
	s >> position >> speed >> acceleration >> color >> spriteName;

	auto *texture = scene.getAssetTexture(spriteName);
	if (texture == nullptr) {
		std::cerr << "Can't load " << spriteName << std::endl;
		return;
	}
	scene.addGameObject<GoProjectile>(position, speed, acceleration, color, *texture);
}

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

static void spawnWeapon(sfs::Scene &scene, Serializer &s, uint64_t id)
{
	uint64_t playerId;
	int32_t weaponType;
	std::string spriteName;

	s >> playerId;
	s >> weaponType;
	s >> spriteName;

	std::cout << "spawning a " << spriteName << std::endl;
	auto *go = scene.getGameObject(playerId);
	auto *texture = scene.getAssetTexture(spriteName);
	if (go == nullptr || texture == nullptr)
		return;
	// add plutot un gameobject weapon
	go->addChild<GoWeapon>(scene, id, playerId, *texture);
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
	case UdpPrctl::spawnType::WEAPON:
		spawnWeapon(scene, s, id);
		break;
	case UdpPrctl::spawnType::PROJECTILE:
		spawnProjectile(scene, s, id);
		break;
	};
	return 0;
}
} // namespace cf