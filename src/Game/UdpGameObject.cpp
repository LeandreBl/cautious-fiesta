#include "UdpGameObject.hpp"

namespace cf {
UdpGameObject::UdpGameObject(uint64_t id) noexcept
{
	*const_cast<uint64_t *>(&_id) = id;
}
} // namespace cf