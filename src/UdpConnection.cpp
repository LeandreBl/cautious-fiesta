#include "UdpConnection.hpp"

namespace cf
{

    void UdpConnect::send(Serializer &packet) noexcept
    {
        if (_socket.send(packet.getNativeHandle(), packet.getSize(), _ip, _port) != sf::Socket::Done)
            std::cout << "error" << std::endl;
    }

    int UdpConnect::setPort(uint16_t port, std::string ip) noexcept
    {
        _port = port;
        _ip = ip;
        if (_socket.bind(port) != sf::Socket::Done) {
            if (_socket.bind(0) != sf::Socket::Done) {
                return -84;
            }
            _socket.setBlocking(false);
            std::cout << "Local port created : " << _socket.getLocalPort() << std::endl;
            return _socket.getLocalPort();
        }
        _socket.setBlocking(false);
        return -1;
    }

    void UdpConnect::pushPacket(Serializer &packet, UdpPrctl::Type type, uint16_t index) noexcept
    {
        Serializer NewPacket(packet, type, index);

        _toWrite.emplace(NewPacket);
        if (index == _queueIndex)
            _queueIndex += 1;
    }

    void UdpConnect::sendInput(UdpPrctl::inputType action, UdpPrctl::inputType type) noexcept
    {
        Serializer packet;
        UdpPrctl::udpInput input = { (int)action, (int)type };

        packet.set(input);
        pushPacket(packet, UdpPrctl::Type::INPUT, _queueIndex);
    }

    void UdpConnect::update(sfs::Scene &) noexcept
    {
        char buffer[1024];
        std::size_t rd;

        if (_queueIndex >= 30000)
            _queueIndex = 0;

        do {
            if (_socket.receive(buffer, sizeof(buffer), rd, _ip, _port) != sf::Socket::Done)
                return;
            else
                _serializer.nativeSet(buffer, rd);
        } while (rd == sizeof(buffer));
        UdpPrctl::udpHeader header;
        while (_serializer.getSize() >= sizeof(header)) {
            _serializer.get(header);
            std::cout << "packet type = " << (int)header.type << std::endl;
            Serializer packet;
            pushPacket(packet, (UdpPrctl::Type)header.type, header.index);
        }

        while (_toWrite.empty() == false) {
            Serializer packet = _toWrite.front();
            send(packet);
            _toWrite.pop();
        }

    }
}
