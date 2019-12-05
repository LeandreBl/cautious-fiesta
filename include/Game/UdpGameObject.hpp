#pragma once

#include <GameObject.hpp>

namespace cf {
class UdpGameObject : public sfs::GameObject {
      public:
	UdpGameObject(uint64_t id) noexcept;
};
} // namespace cf
