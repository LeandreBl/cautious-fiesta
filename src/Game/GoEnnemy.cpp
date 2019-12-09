#include <math.h>

#include "GoEnnemy.hpp"
#include "SpriteSheetLoader.hpp"

namespace cf
{
GoEnnemy::GoEnnemy(uint64_t id, const std::string &name, const std::string &sprite) noexcept
    : UdpGameObject(id), _spriteSheet(sprite), _ennemySprite(nullptr), _velocity(addComponent<sfs::Velocity>())
{
    UdpGameObject::name(name);
}

void GoEnnemy::start(sfs::Scene &scene) noexcept
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
    _ennemySprite = &addComponent<sfs::MultiSprite>(*texture, v);
}

void GoEnnemy::update(sfs::Scene &scene) noexcept
{
}
} // namespace cf