#include <BasicShape.hpp>

#include "Velocity.hpp"
#include "UdpGameObject.hpp"
#include "Udp.hpp"

namespace cf
{
class GoEnnemy : public UdpGameObject
{
public:
    GoEnnemy(uint64_t id, const std::string &name, const std::string &sprite) noexcept;
    void start(sfs::Scene &scene) noexcept;
    void update(sfs::Scene &scene) noexcept;

protected:
    std::string _spriteSheet;
    sfs::MultiSprite *_ennemySprite;
    sfs::Velocity &_velocity;
};
} // namespace cf