#pragma once

#include <GameObject.hpp>

namespace cf
{
    class UdpConnect : public sfs::GameObject
    {
        public:
            void setPort(uint16_t port) noexcept {_port = port;};
        protected:
            uint16_t _port;
    };
}