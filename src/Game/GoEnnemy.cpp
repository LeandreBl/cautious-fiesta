#include <math.h>

#include "GoEnnemy.hpp"
#include "SpriteSheetLoader.hpp"
#include "Vector.hpp"
#include "GoPlayer.hpp"

namespace cf
{
GoEnnemy::GoEnnemy(GameManager &manager, uint64_t id, const std::string &name, const std::string &sprite) noexcept
    : UdpGameObject(id), _manager(manager), _spriteSheet(sprite), _ennemySprite(nullptr), _velocity(addComponent<sfs::Velocity>())
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
    auto *go = _manager.getNearestPlayer(getPosition());
    if (go == nullptr)
        return;
    float angle = sfs::angle(getPosition(), go->getPosition());
    _ennemySprite->setRotation(angle * 180 / M_PI - 45);
}
} // namespace cf