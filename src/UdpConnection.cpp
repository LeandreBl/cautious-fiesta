#include "UdpConnection.hpp"

namespace cf
{
    void UdpConnect::setPort(uint16_t port, std::string ip) noexcept
    {
        _port = port;
        _ip = ip;
        if (_socket.bind(port) != sf::Socket::Done)
            std::cout << "fail to bin the udp socket to the port : " << _port << std::endl;
        _socket.setBlocking(false);
    }

    void UdpConnect::update(sfs::Scene &) noexcept
    {
        char buffer[1024];
        std::size_t rd;

        do {
            if (_socket.receive(buffer, sizeof(buffer), rd, _ip, _port) != sf::Socket::Done)
                return;
            else
                _serializer.nativeSet(buffer, rd);
        } while (rd == sizeof(buffer));
        std::cout << "Received " << rd << " bytes from " << _ip << " on port " << _port << std::endl;
        UdpPrctl::udpHeader header;
        while (_serializer.getSize() >= sizeof(header)) {
            _serializer.get(header);
            UdpPrctl udp((UdpPrctl::type)header.type, header.size, header.index);
            if (udp.isCorrect())
                std::cout << "packet type = " << udp.getType() << std::endl;
        }
    }
}