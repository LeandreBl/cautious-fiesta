#pragma once

#include <GameObject.hpp>
#include <SFML/Network.hpp>
#include "Serializer.hpp"
#include "Udp.h"

namespace cf
{
    class UdpConnect : public sfs::GameObject
    {
        public:
            void setPort(uint16_t port, std::string ip) noexcept;
            void update(sfs::Scene &) noexcept;
        protected:
            uint16_t _port;
            sf::IpAddress _ip;
            sf::UdpSocket _socket;
            Serializer _serializer;
    };
}