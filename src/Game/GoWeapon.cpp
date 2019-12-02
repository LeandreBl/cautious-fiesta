#include "GoWeapon.hpp"

namespace cf
{
GoWeapon::GoWeapon(uint64_t id, uint64_t playerId, const sf::Texture &texture) noexcept
    : UdpGameObject(id), _weaponSprite(addComponent<sfs::Sprite>(texture))
{
}

void GoWeapon::start(sfs::Scene &scene) noexcept
{
    auto *font = scene.getAssetFont("");
    if (font == nullptr)
    {
        std::cerr << "no font found" << std::endl;
        destroy();
        return;
    }
    auto pRect = _weaponSprite.getLocalBounds();
}

void GoWeapon::update(sfs::Scene &scene) noexcept
{
}

} // namespace cf