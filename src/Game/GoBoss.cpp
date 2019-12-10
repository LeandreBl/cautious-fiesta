#include <math.h>

#include "GoBoss.hpp"
#include "SpriteSheetLoader.hpp"

namespace cf
{
GoBoss::GoBoss(uint64_t id, const std::string &name, const std::string &sprite) noexcept
    : UdpGameObject(id), _spriteSheet(sprite), _bossSprite(nullptr), _velocity(addComponent<sfs::Velocity>())
{
    UdpGameObject::name(name);
}

void GoBoss::start(sfs::Scene &scene) noexcept
{
    SpriteSheetLoader loader(_spriteSheet);
    auto path = loader.getSpritePath();
    auto v = loader.getFrames();
    auto *texture = scene.getAssetTexture(path);

    if (texture == nullptr)
    {
        std::cerr << _spriteSheet << " texture not found" << std::endl;
        destroy();
        return;
    }
    _bossSprite = &addComponent<sfs::MultiSprite>(*texture, v);
}

void GoBoss::update(sfs::Scene &scene) noexcept
{
}
} // namespace cf