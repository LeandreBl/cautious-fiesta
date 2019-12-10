#include "GoWeapon.hpp"

namespace cf {
GoWeapon::GoWeapon(uint64_t id, uint64_t playerId, const sf::Texture &texture) noexcept
	: UdpGameObject(id)
	, _weaponSprite(addComponent<sfs::Sprite>(texture))
{
	_layer = 6;
}

void GoWeapon::start(sfs::Scene &scene) noexcept
{
	auto *font = scene.getAssetFont("");
	if (font == nullptr) {
		std::cerr << "no font found" << std::endl;
		destroy();
		return;
	}
	if (parent() != nullptr) {
		setPosition(parent()->getPosition());
		auto v = parent()->getComponents<sfs::Sprite>();
		if (!v.empty()) {
			_weaponSprite.setOrigin(0, 0);
			_weaponSprite.setScale(1.5, 1.5);
		}
	}
}

void GoWeapon::update(sfs::Scene &scene) noexcept
{
	if (parent() != nullptr) {
		setPosition(parent()->getPosition());
		auto v = parent()->getComponents<sfs::Sprite>();
		if (!v.empty())
			_weaponSprite.setRotation(v[0]->getRotation());
	}
}
} // namespace cf