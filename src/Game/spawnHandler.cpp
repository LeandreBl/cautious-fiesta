#include "GameManager.hpp"
#include "UdpConnection.hpp"
#include "GoPlayer.hpp"
#include "GoWeapon.hpp"
#include "GoObstacle.hpp"
#include "GoProjectile.hpp"
#include "SpriteSheetLoader.hpp"
#include "UiWeapon.hpp"

namespace cf {

static void spawnProjectile(sfs::Scene &scene, Serializer &s, uint64_t id, GameManager &manager)
{
	sf::Vector2f position;
	float angle;
	float speed;
	sf::Color color;
	std::string spriteSheet;
	s >> position >> angle >> speed >> color >> spriteSheet;

	SpriteSheetLoader loader(spriteSheet);
	auto *texture = scene.getAssetTexture(loader.getSpritePath());
	if (texture == nullptr) {
		std::cerr << "Can't load " << spriteSheet << std::endl;
		return;
	}
	scene.addGameObject<GoProjectile>(id, position, angle, speed, color, *texture, loader.getFrames());
}

static void spawnObstacle(sfs::Scene &scene, Serializer &s, uint64_t id, GameManager &manager)
{
	sf::Vector2f position;
	std::string spriteSheet;
	s >> position >> spriteSheet;

	SpriteSheetLoader loader(spriteSheet);
	auto *texture = scene.getAssetTexture(loader.getSpritePath());
	if (texture == nullptr) {
		std::cerr << "Can't load " << spriteSheet << std::endl;
		return;
	}
	scene.addGameObject<GoObstacle>(id, position, *texture, loader.getFrames());
}

static void spawnPlayer(sfs::Scene &scene, Serializer &s, uint64_t id, GameManager &manager)
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
	auto &go = scene.addGameObject<GoPlayer>(id, name, stats, color, sprite,
						 static_cast<UdpPrctl::weaponType>(weaponType));
	if (name == manager._character.getName()) {
		manager._self = &go;
	}
}

static void spawnWeapon(sfs::Scene &scene, Serializer &s, uint64_t id, GameManager &manager)
{
	uint64_t playerId;
	int32_t weaponType;
	std::string spriteName;

	s >> playerId;
	s >> weaponType;
	s >> spriteName;

	auto *go = scene.getGameObject(playerId + 1000);
	auto *texture = scene.getAssetTexture(spriteName);
	if (go == nullptr || texture == nullptr)
		return;
	go->addChild<GoWeapon>(scene, id, playerId, *texture);

	auto v = scene.getGameObjects<UiWeapon>();
	if (v.empty() == false)
		v[0]->setUiWeapon(*texture);
}

int UdpConnect::spawnHandler(sfs::Scene &scene, GameManager &manager, Serializer &s)
{
	int32_t type;
	uint64_t id;

	s >> type;
	s >> id;
	id += 1000;
	switch (static_cast<UdpPrctl::spawnType>(type)) {
	case UdpPrctl::spawnType::PLAYER:
		spawnPlayer(scene, s, id, _manager);
		break;
	case UdpPrctl::spawnType::OBSTACLE:
		spawnObstacle(scene, s, id, _manager);
		break;
	case UdpPrctl::spawnType::WEAPON:
		spawnWeapon(scene, s, id, _manager);
		break;
	case UdpPrctl::spawnType::PROJECTILE:
		spawnProjectile(scene, s, id, _manager);
		break;
	};
	return 0;
}
} // namespace cf
